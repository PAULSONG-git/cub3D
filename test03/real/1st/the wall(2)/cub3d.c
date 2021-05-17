#include "cub3d.h"
/*
void	ft_draw(t_all *s)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	s->ray = ray;
	s->hit = hit;
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}
*/
int		ft_cubed(t_all s, char *cub, int bmp)
{
	t_pos	pos;
	//t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	pos.th = 0;
	s.pos = pos;
	
	//s.mlx.ptr = mlx_init();
	ft_parse(&s, cub);
	
		/* print map */
    for( int y=s.map.y-1; y>=0; y-- ) {
        for( int x=0; x<s.map.x; x++ ) {
        	printf("%c", s.map.tab[x][y]);
		}
        putchar('\n');
    }

	for( int x=0; x<s.map.x; x++ ) {
        double wdist = cast_single_ray(&s, x);
        printf("** ray %3d : dist %.2f\n", x, wdist);
    }
	/*
	if (bmp == 1)
		return (ft_bitmap(&s));
	ft_rotate(&s, 1);
	ft_move(&s, 1);
	ft_rotate(&s, -1);
	ft_move(&s, -1);
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);
	*/
	return (1);
}

double		cast_single_ray(t_all *s, int x)
{
    double ray = (s->pos.th + FOVH_2) - (x * s->win.ANGLE_PER_PIXEL);

    dir_t wdir;     /* direction of wall */
    double wx, wy;  /* coord. of wall intersection point */

    if( get_wall_intersection(s, ray, s->pos.x, s->pos.y, &wdir, &wx, &wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(s->pos.x, s->pos.y, wx, wy);

    return wdist;
}

bool
get_wall_intersection(t_all *s,  double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
        rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

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
            printf(" V(%d, %.2f) ->", mapx, f);
        }
        else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
            printf(" H(%.2f, %d) ->", g, mapy);
        }
        int cell = map_get_cell(s, mapx, mapy);
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
            printf(" hit wall!\n");
            break;
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

int
map_get_cell(t_all *s, int x, int y )
{
	char c;
	int  n;

	n = 0;
	c = s->map.tab[x][y];
	if (c == '1')
		n = 1;
	else if (c == '2')
		n = 2;
	return ((x >= 0 && x < s->map.x && y >= 0 && y < s->map.y) ? n : -1);
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

void	ft_declare(t_all s, char *cub, int bmp)
{
	
	t_map	map;
	/*t_tex	tex;
	t_spr	*spr;
	t_stk	*stk;
*/
	map.tab = NULL;
/*	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	spr = NULL;
	stk = NULL;*/
	map.x = 0;
	map.y = 0;
	/*
	map.spr = 0;
	tex.c = NONE;
	tex.f = NONE;
	*/
	s.map = map;
	/*s.tex = tex;
	s.spr = spr;
	s.stk = stk;
	*/
	ft_cubed(s, cub, bmp);
}

void	ft_init(char *cub, int bmp)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	//t_err	err;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.data = NULL;
	win.x = 0;
	win.y = 0;
	win.ANGLE_PER_PIXEL = 0;
	win.FOV_V = 0;
	//err.n = 0;
	//err.m = 0;
	//err.p = 0;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	//s.err = err;
	ft_declare(s, cub, bmp);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_namecheck(av[1], "cub") && ft_savecheck(av[2], "--save"))
		ft_init(av[1], 1);
	else if (ac == 2 && ft_namecheck(av[1], "cub"))
		ft_init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
