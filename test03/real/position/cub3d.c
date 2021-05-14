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