/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 19:09:08 by paul              #+#    #+#             */
/*   Updated: 2021/05/21 19:21:04 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw(t_all *s)
{
	int x;
	int y;

	y = -1;
	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.data = (int *)mlx_get_data_addr(s->img.ptr, &s->img.bpp,
			&s->img.size_l, &s->img.endian);
	while (++y < s->win.y / 2)
	{
		x = -1;
		while (++x < s->win.x)
			s->img.data[s->win.x * y + x] = s->tex.c;
	}
	while (++y < s->win.y)
	{
		x = -1;
		while (++x < s->win.x)
			s->img.data[s->win.x * y + x] = s->tex.f;
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

	pos.x = 0;
	pos.y = 0;
	pos.th = 0;
	s.pos = pos;
	s.mlx.ptr = mlx_init();
	if (ft_parse(&s, cub) == -1)
		return (ft_close(&s, 0));
	sprite_init(&s);
	if (bmp == 1)
		return (ft_bitmap(&s));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "ex02");
	ft_draw(&s);
	mlx_hook(s.win.ptr, X_EVENT_KEY_PRESS, 0, &key_press, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

void	ft_declare(t_all s, char *cub, int bmp)
{
	t_map	map;
	t_tex	tex;
	t_spr	*spr;

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	tex.zbuf = NULL;
	spr = NULL;
	map.x = 0;
	map.y = 0;
	map.l = 0;
	tex.c = NONE;
	tex.f = NONE;
	tex.tx = 0;
	tex.ty = 0;
	tex.wx = 0;
	tex.wy = 0;
	s.map = map;
	s.tex = tex;
	s.spr = spr;
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
	win.a_p_pixel = 0;
	win.fov_h = 0;
	win.fov_v = 0;
	win.fovh_2 = 0;
	err.n = 0;
	err.m = 0;
	err.p = 0;
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
