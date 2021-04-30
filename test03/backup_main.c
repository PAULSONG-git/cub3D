#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mlx/mlx.h"

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

#define  SX        	1920	/* screen width */
#define  SY			1080	/* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V		(FOV_H*(double)SY/(double)SX)
#define  WALL_H		1.0

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

#define  _2PI       6.28318530717958647692  /* 2 * M_PI */

#define  ROT_UNIT   0.03    /* rad */
#define  MOVE_UNIT  0.1

enum { KEY_OTHER, KEY_W, KEY_A, KEY_S, KEY_D, KEY_LEFT, KEY_RIGHT, KEY_ESC };

typedef struct {
    double px;
    double py;
    double th;
} player_t;

enum { VERT, HORIZ };

typedef enum { false=0, true=1 } bool;
typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

#define  MAPX   11
#define  MAPY   15

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	//You don't need to understand the 3 values below.
	//After declaration, it will be automatically initialized when passed to mlx_get_data_addr function.
	//아래 3개 값은 이해 안해도 사용하는데 지장이 없음.
	//선언한뒤 함수의 인자로만 잘 넣어주면 알아서 정보를 받아나옴.
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

int
map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

int
sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double
l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

bool
get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    double f=INFINITY, g=INFINITY;
    bool hit = false;
    int hit_side; /* either VERT or HORIZ */

    while( !hit )
    {
        int mapx, mapy;

        if( xstep != 0 ) f = xslope * (nx-px) + py;
        if( ystep != 0 ) g = yslope * (ny-py) + px;

        /* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
        double dist_v = l2dist(px, py, nx, f);
        double dist_h = l2dist(px, py, g, ny);

        if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
            mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
            mapy = (int) f;
            hit_side = VERT;
        }
        else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
        }
        int cell = map_get_cell(mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_W : DIR_E;
                *wx = nx;
                *wy = f;
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_S : DIR_N;
                *wx = g;
                *wy = ny;
            }
            hit = true;
            break;
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

double
cast_single_ray( int x, player_t *pp, dir_t* wdir)
{
    double ray = (pp->th + FOVH_2) - (x * ANGLE_PER_PIXEL);

    double wx, wy;  /* coord. of wall intersection point */

    if( get_wall_intersection(ray, pp->px, pp->py, wdir, &wx, &wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(pp->px, pp->py, wx, wy);
	wdist *= cos(pp->th - ray);  /* 보정 */

    return wdist;
}

int
get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

void
draw_wall( void* mlx, t_img *img, void* win, double wdist, int x, int color)
{
	int count_h;
	int wh = get_wall_height(wdist);    /* wall height, in pixels */
    /* starting/ending y pos of the wall slice */
    int y0 = (int)((SY - wh)/2.0);
    int y1 = y0 + wh - 1;

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SY-1, y1);

	count_h = ystart -1;
	while (++count_h < yend)
		img->data[count_h * SX + x] = 0x718F94;
}

void
render( void* mlx, t_img *img, void* win, player_t* pp )
{
    static int wall_colors[] = {    /* DIR_N, E, W, S */
        0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
    };
    
    for( int x=0; x<SX; x++ ) {
        dir_t wdir;     /* direction of wall */
        double wdist = cast_single_ray(x, pp, &wdir);
        draw_wall(mlx, img, win, wdist, x, wall_colors[wdir]);
    }
    mlx_put_image_to_window(mlx, win, img->img_ptr, 0, 0);
}

int
main( int ac, char** av )
{
	void	*mlx;
	void	*win;
	t_img 	img;

	/* print map */
    for( int y=MAPY-1; y>=0; y-- ) {
        for( int x=0; x<MAPX; x++ ) {
            printf("%c ", (map_get_cell(x,y)==1 ? '#':'.'));
        }
        putchar('\n');
    }

    if( ac != 4 ) {
        fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
        exit(1);
    }

    player_t pl;
    pl.px = atof(av[1]);
    pl.py = atof(av[2]);
    pl.th = deg2rad(atof(av[3]));

	mlx = mlx_init();
	win = mlx_new_window(mlx, SX, SY, "ex03");
	img.img_ptr = mlx_new_image(mlx, SX, SY);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	render(mlx, &img, win, &pl);
    
	mlx_loop(mlx);

    return 0;
}
