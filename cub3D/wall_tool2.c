/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tool2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 20:45:38 by psong             #+#    #+#             */
/*   Updated: 2021/05/24 20:52:53 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double				min(double a, double b)
{
	if (b > a)
		return (a);
	return (b);
}

double				max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

int					get_wall_height(t_all *s, double dist)
{
	double				fov_h;

	fov_h = 2.0 * dist * tan(s->win.fov_v / 2.0);
	return ((int)(s->win.y * (WALL_H / fov_h)));
}

void				render(t_all *s)
{
	int					x;
	int					wdir;
	double				wdist;
	double				txratio;

	x = 0;
	while (x < s->win.x)
	{
		wdist = cast_single_ray(s, x, &wdir);
		s->tex.zbuf[x] = wdist;
		if (wdir == DIR_W || wdir == DIR_E)
			txratio = s->tex.wy - floor(s->tex.wy);
		else
			txratio = s->tex.wx - floor(s->tex.wx);
		s->tex.tx = (int)(floor(txratio * 64));
		draw_wall(s, wdist, x, wdir);
		x++;
	}
	draw_sprites(s);
}

int					get_wall_intersection4(t_all *s, int cell,
		double dist_v, double dist_h)
{
	if (s->w.xstep != 0)
		s->w.f = s->w.xslope * (s->w.nx - s->pos.x) + s->pos.y;
	if (s->w.ystep != 0)
		s->w.g = s->w.yslope * (s->w.ny - s->pos.y) + s->pos.x;
	dist_v = l2dist(s->pos.x, s->pos.y, s->w.nx, s->w.f);
	dist_h = l2dist(s->pos.x, s->pos.y, s->w.g, s->w.ny);
	if (dist_v < dist_h)
	{
		s->w.mapx = (s->w.xstep == 1) ? (int)(s->w.nx) : (int)(s->w.nx) - 1;
		s->w.mapy = (int)s->w.f;
		s->w.hit_side = VERT;
	}
	else
	{
		s->w.mapx = (int)s->w.g;
		s->w.mapy = (s->w.ystep == 1) ? (int)(s->w.ny) : (int)(s->w.ny) - 1;
		s->w.hit_side = HORIZ;
	}
	cell = map_get_cell(s, s->w.mapx, s->w.mapy);
	return (cell);
}
