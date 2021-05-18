#include "cub3d.h"

void	ft_draw(t_all *s)
{
/*	t_ray	ray;
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
	*/
	int x;
	int y;
	y = -1;
	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.data = (int *)mlx_get_data_addr(s->img.ptr, &s->img.bpp, &s->img.size_l, &s->img.endian);
	while (++y < s->win.y)
	{
		x = -1;
		while (++x < s->win.x)
			s->img.data[s->win.x * y + x] = 0x000000;
	}
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	render(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.data);
}

int		ft_cubed(t_all s, char *cub, int bmp)
{
	t_pos	pos;
	//t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	pos.th = 0;
	s.pos = pos;
	int color = 0x00FF0000;
	
	s.mlx.ptr = mlx_init();
	//ft_parse(&s, cub);
	if (ft_parse(&s, cub) == -1)
		return (ft_close(&s, 0));
	int a = 0;
	int b = 0;
	char **tmp;
	
	tmp = malloc(sizeof(char *) * (s.map.x + 1));
	while (a < s.map.x)
	{
		tmp[a] = malloc(sizeof(char) * (s.map.l + 1));
		while (s.map.tab[a][b] != '\0')
		{
			tmp[a][b] = s.map.tab[a][b];
			b++;
		}
		while (b < s.map.l)
		{
			tmp[a][b] = ' ';
			b++;
		}
		tmp[a][b] = '\0';
		b = 0;
		a++;
	}
	tmp[a] = NULL;
	s.map.tab = tmp;

	a = 0;
	b = 0;
	int c = 0;
	while (a < s.map.x)
	{
		while (b < s.map.l)
		{
			if (tmp[a][b] == '1' || tmp[a][b] == ' ')
				c = 0;
			else
			{
				if (tmp[a][b+1] == ' ')
					c = 1;	
				if (b > 0)
				{
					if (tmp[a][b-1] == ' ')
						c = 1;
					if (a > 0)
						if(tmp[a-1][b-1] == ' ')
							c = 1;
				}
				if (a < s.map.x - 1)
				{
					if (tmp[a+1][b] == ' ')
						c = 1;
					if (b > 0)
						if (tmp[a+1][b-1] == ' ')
							c = 1;
					if (tmp[a+1][b+1] == ' ')
						c = 1;
				}
				if (a > 0)
				{
					if (tmp[a-1][b] == ' ')
						c = 1;
					if (tmp[a-1][b+1] == ' ')
						c = 1;
				}
				if (a == 0 || a == s.map.x -1 || b == 0 || b == s.map.l -1)
					c = 1;
			}
			if (c == 1)
			{	
				ft_strerror(-19);
			return (ft_close(&s, 0));
			}
			b++;
		}
		b = 0;
		a++;
	}
	if (c == 1)
	{
		ft_strerror(-19);
	}

	ft_pos(&s);
	errorcheck2(&s);

	//s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "ex02");
	//s.img.ptr = mlx_new_image(s.mlx.ptr, s.win.x, s.win.y);
	//s.img.data = (int *)mlx_get_data_addr(s.img.ptr, &s.img.bpp, &s.img.size_l, &s.img.endian);

	if (!(s.tex.visible = (int **)malloc(sizeof(int *) * s.map.x)))
		return (-1);
	for (int i = 0; i < s.map.x; i++)
	{
		if (!(s.tex.visible[i] = (int *)malloc(sizeof(int) * s.map.y)))
			return (-1);
	}
	for (int i = 0; i < s.map.x; i++)
	{
		for (int j = 0; j < s.map.y; j++)
			s.tex.visible[i][j] = 0;
	}

	if (!(s.tex.zbuf = (double *)malloc(sizeof(double) * s.win.x)))
		return (-1);
	if (bmp == 1)
		return (ft_bitmap(&s));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "ex02");
	ft_draw(&s);
	mlx_hook(s.win.ptr, X_EVENT_KEY_PRESS, 0, &key_press, &s);
		
		/* print map */
    /*for( int y=s.map.l-1; y>=0; y-- ) {
        for( int x=0; x<s.map.x; x++ ) {
        	printf("%c", s.map.tab[x][y]);
		}
        putchar('\n');
    }*/
	//printf("%d\n", s.map.x);
	//printf("%d\n", s.map.y);
	
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
	mlx_loop(s.mlx.ptr);
	return (1);
}

static int
cmp_sprites( const void* a, const void* b )
{
    return (((const t_spr*)a)->dist > ((const t_spr*)b)->dist) ? -1 : 1;
}

static t_spr*
get_visible_sprites( t_all *s, int* pcnt )
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


static void
draw_sprites( t_all *s )
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


int				key_press(int key, t_all *s)
{
	static int a = 0;

	if(key == KEY_ESC )
		exit(0);
	if( key == KEY_LEFT || key == KEY_RIGHT ) {
            player_rotate(s, ROT_UNIT * (key==KEY_LEFT ? 1 : -1));
			ft_draw(s);
        }
    else if( key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D ) {
            if( player_move(s, key, MOVE_UNIT) == 0 ) {
			ft_draw(s);
            }
	}
	return (0);
}

int				key_release(int key, t_all *s)
{
	static int a = 0;

	if(key == KEY_ESC )
		exit(0);
	if( key == KEY_LEFT || key == KEY_RIGHT ) {
            player_rotate(s, ROT_UNIT * (key==KEY_LEFT ? 1 : -1));
            render(s);
        }
    else if( key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D ) {
            if( player_move(s, key, MOVE_UNIT) == 0 ) {
                render(s);
            }
	}
	return (0);
}

void
player_rotate( t_all* s, double th )
{
    s->pos.th += th;
    if( s->pos.th < 0 ) s->pos.th += _2PI;
    else if( s->pos.th > _2PI ) s->pos.th -= _2PI;
}

static int
get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
		default: /* invalid */
            return -1;
    }
    return 0;
}

int
player_move( t_all *s, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(s->pos.th, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = s->pos.x + dx;
    ny = s->pos.y + dy;

    if( map_get_cell(s, (int)nx, (int)ny) != 0) {
        printf("** bump !\n");
        return -1;
    }
    s->pos.x = nx;
    s->pos.y = ny;
    return 0;
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
    //mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	//free(s->img.ptr);
	//free(s->img.data);
}

int
get_wall_height(t_all *s, double dist )
{
    double fov_h = 2.0 * dist * tan(s->win.FOV_V/2.0);
    return (int)(s->win.y * (WALL_H / fov_h)); /* in pixels */
}

void
draw_wall(t_all *s, double wdist, int x, int color )
{
    int wh = get_wall_height(s, wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((s->win.y - wh)/2.0);
    int y1 = y0 + wh - 1;

	int xx;
xx = -1;
while (++xx < s->win.y / 2)
	s->img.data[xx * s->win.x + x] = s->tex.c;
while (++xx < s->win.y)
	s->img.data[xx * s->win.x + x] = s->tex.f;

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
    double ray = (s->pos.th + FOVH_2) - (x * s->win.ANGLE_PER_PIXEL);

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
			s->tex.visible[mapx][mapy] = 1;  /* 이 행을 추가 ! */

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
	t_tex	tex;
	t_spr	*spr;
	//t_stk	*stk;

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	tex.visible = NULL;
	tex.zbuf = NULL;
	//spr = NULL;
	//stk = NULL;
	map.x = 0;
	map.y = 0;
	map.l = 0;
	
	//map.spr = 0;
	tex.c = NONE;
	tex.f = NONE;

	tex.tx = 0;
	tex.ty = 0;
	tex.wx = 0;
	tex.wy = 0;
	s.map = map;
	s.tex = tex;
	s.spr = spr;
	//s.stk = stk;
	
	ft_cubed(s, cub, bmp);
}

void	ft_init(char *cub, int bmp)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.data = NULL;
	win.x = 0;
	win.y = 0;
	win.ANGLE_PER_PIXEL = 0;
	win.FOV_V = 0;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	err.R = 0; 
	err.NO = 0;
	err.SO = 0;
	err.WE = 0;
	err.EA = 0;
	err.S = 0;
	err.F = 0;
	err.C = 0;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.err = err;
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
