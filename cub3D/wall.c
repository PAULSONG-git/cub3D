#include "cub3d.h"

int
get_wall_height(t_all *s, double dist )
{
    double fov_h = 2.0 * dist * tan(s->win.fov_v/2.0);
    return (int)(s->win.y * (WALL_H / fov_h)); /* in pixels */
}

void
draw_wall(t_all *s, double wdist, int x, int color )
{
    int wh = get_wall_height(s, wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((s->win.y - wh)/2.0);
    int y1 = y0 + wh - 1;

/*	int xx;
xx = -1;
while (++xx < s->win.y / 2)
	s->img.data[xx * s->win.x + x] = s->tex.c;
while (++xx < s->win.y)
	s->img.data[xx * s->win.x + x] = s->tex.f;
*/
    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(s->win.y-1, y1);
	
	int count_h = ystart -1;
	while (++count_h < yend)
	{
		s->tex.ty = (int)((double)(count_h - y0) * 64 / wh);
		if (color == 0)
			s->img.data[count_h * s->win.x + x] = s->tex.n[64 * s->tex.ty + s->tex.tx];
		if (color == 1)
			s->img.data[count_h * s->win.x + x] = s->tex.e[64 * s->tex.ty + s->tex.tx];
		if (color == 2)
			s->img.data[count_h * s->win.x + x] = s->tex.w[64 * s->tex.ty + s->tex.tx];
		if (color == 3)
			s->img.data[count_h * s->win.x + x] = s->tex.s[64 * s->tex.ty + s->tex.tx];
	}
}

double		cast_single_ray(t_all *s, int x, dir_t *wdir)
{
    double ray = (s->pos.th + s->win.fovh_2) - (x * s->win.a_p_pixel);

    if( get_wall_intersection(s, ray, s->pos.x, s->pos.y, wdir, &s->tex.wx, &s->tex.wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(s->pos.x, s->pos.y, s->tex.wx, s->tex.wy);
	wdist *= cos(s->pos.th - ray);  /* 보정 */

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
            break;
        }
			//s->tex.visible[mapx][mapy] = 1;  /* 이 행을 추가 ! */

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */
    return hit;
}

void
render( t_all *s )
{
    for( int x=0; x<s->win.x; x++ ) {
        dir_t wdir;     /* direction of wall */
        double wdist = cast_single_ray(s, x, &wdir);
		s->tex.zbuf[x] = wdist;
		
		double txratio = (wdir == DIR_W || wdir == DIR_E) ? (s->tex.wy-floor(s->tex.wy)) : (s->tex.wx-floor(s->tex.wx));
    	s->tex.tx = (int)(floor(txratio * 64)); /* texture col # */
		draw_wall(s, wdist, x, wdir);

		/* draw sprites using visibility & distances */
    }
	draw_sprites(s);
}

