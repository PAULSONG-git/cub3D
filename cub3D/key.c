/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:32:47 by psong             #+#    #+#             */
/*   Updated: 2021/05/24 13:37:15 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_close(t_all *s, int win)
{
	int					i;

	i = 0;
	while (i < s->map.x)
		free(s->map.tab[i++]);
	free(s->map.tab);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	free(s->tex.i);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(0);
	return (1);
}

int					key_press(int key, t_all *s)
{
	if (key == ESC)
		exit(0);
	if (key == LEFT || key == RIGHT)
	{
		player_rotate(s, ROTUNIT * (key == LEFT ? 1 : -1));
		ft_draw(s);
	}
	else if (key == W || key == A || key == S || key == D)
	{
		if (player_move(s, key) == 0)
			ft_draw(s);
	}
	return (0);
}

void				player_rotate(t_all *s, double th)
{
	s->pos.th += th;
	if (s->pos.th < 0)
		s->pos.th += TWOPI;
	else if (s->pos.th > TWOPI)
		s->pos.th -= TWOPI;
}

int					get_move_offset(double th, int key,
		double *pdx, double *pdy)
{
	double				amt;

	amt = MOVEUNIT;
	if (key == W || key == S)
	{
		*pdx = (key == W ? 1 : -1) * amt * cos(th);
		*pdy = (key == W ? 1 : -1) * amt * sin(th);
	}
	else if (key == A || key == D)
	{
		*pdx = amt * cos(th + (key == A ? 1 : -1) * M_PI_2);
		*pdy = amt * sin(th + (key == A ? 1 : -1) * M_PI_2);
	}
	else
		return (-1);
	return (0);
}

int					player_move(t_all *s, int key)
{
	double				dx;
	double				dy;
	double				nx;
	double				ny;

	dx = 0;
	dy = 0;
	if (get_move_offset(s->pos.th, key, &dx, &dy) < 0)
		return (-1);
	nx = s->pos.x + dx;
	ny = s->pos.y + dy;
	if (map_get_cell(s, (int)nx, (int)ny) != 0)
	{
		printf("** bump !\n");
		return (-1);
	}
	s->pos.x = nx;
	s->pos.y = ny;
	return (0);
}
