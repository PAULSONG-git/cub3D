#include "cub3d.h"

int     cmp_sprites( const void* a, const void* b )
{
    return (((const t_spr*)a)->dist > ((const t_spr*)b)->dist) ? -1 : 1;
}

t_spr*  get_visible_sprites( t_all *s, int* pcnt )
{
    int n = 0;
    t_spr *sp = NULL; /* dynamic array */

    /* build list of visible sprites */
    for( int x=0; x < s->map.x; x++ ) {
        for( int y=0; y<s->map.y; y++ ) {
            if( map_get_cell(s, x, y) <= 1 )
                continue;

            if( n == 0 ) sp = (t_spr*) malloc(sizeof(t_spr));
            else sp = (t_spr*) realloc(sp, sizeof(t_spr)*(n+1));

            sp[n].tex = map_get_cell(s, x, y) + 2;
            sp[n].x = x;
            sp[n].y = y;
            sp[n].th = atan2((y+0.5)-(s->pos.y), (x+0.5)-(s->pos.x));
            if( sp[n].th < 0 ) sp[n].th += _2PI;
            sp[n].dist = l2dist(s->pos.x, s->pos.y, x+0.5, y+0.5) * cos(s->pos.th - sp[n].th);
            n++;
        }
    }
    *pcnt = n;
    return sp;
}

int     sprite_init(t_all *s)
{
if (!(s->tex.visible = (int **)malloc(sizeof(int *) * s->map.x)))
		return (-1);
	for (int i = 0; i < s->map.x; i++)
	{
		if (!(s->tex.visible[i] = (int *)malloc(sizeof(int) * s->map.y)))
			return (-1);
	}
	for (int i = 0; i < s->map.x; i++)
	{
		for (int j = 0; j < s->map.y; j++)
			s->tex.visible[i][j] = 0;
	}

	if (!(s->tex.zbuf = (double *)malloc(sizeof(double) * s->win.x)))
		return (-1);
    return (0);
}

void draw_sprites( t_all *s )
{
    int nsp = 0;
	double PIXEL_PER_ANGLE = (s->win.x-1) / FOV_H;
    t_spr *sp = get_visible_sprites(s, &nsp);

    qsort(sp, nsp, sizeof(t_spr), cmp_sprites);  /* order by dist DESC */

    for( int i=0; i<nsp; i++ ) {
        int sh = get_wall_height(s, sp[i].dist); /* sprite height (=width) */
        int color = (sp[i].tex);

        double angle = sp[i].th - s->pos.th; /* angle of sprite relative to FOV center */
        if( angle > M_PI ) angle -= _2PI;   /* ensures -pi < angle < +pi */
        else if( angle < -M_PI ) angle += _2PI;

        int cx = (int)((FOVH_2 - angle) * PIXEL_PER_ANGLE); /* screen pos of sprite, in pixels */
        int xmin = max(0, cx - sh/2); /* clipping */
        int xmax = min(s->win.x, cx + sh/2);

        for( int x=xmin; x<xmax; x++ ) {
            if( sp[i].dist > s->tex.zbuf[x] ) continue; /* behind wall */
			if( sp[i].dist < 0.3 ) continue; /* too close */
			int color2;

            double txratio = (double)(x-cx)/sh + 0.5;
            int tx = (int)(txratio * 64); /* texture col # */
            int y0 = (int)((s->win.y - sh)/2.0);

            for( int y=max(0, y0); y<min(s->win.y, y0+sh); y++ ) {
                int ty = (int)((double)(y-y0) * 64/ sh); /* texture row # */
				color2 = s->tex.i[64 * ty + tx];
                if( (color2 & 0x00ffffff) == 0 ) continue; /* black == transparent */
				s->img.data[y * s->win.x + x] = s->tex.i[64 * (ty) + (tx)];
            }
        }
    }
    if( nsp > 0 ) free(sp);
}