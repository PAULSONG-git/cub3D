/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:47:25 by psong             #+#    #+#             */
/*   Updated: 2021/05/27 11:49:52 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				draw_wall(t_all *s, double wdist, int x, int color)
{
	int wh;
	int y0;
	int y1;
	int c;

	wh = get_wall_height(s, wdist);
	y0 = (int)((s->win.y - wh) / 2.0);
	y1 = y0 + wh - 1;
	c = max(0, y0 - 1);
	while (++c < min(s->win.y - 1, y1))
	{
		s->tex.ty = (int)((double)(c - y0) * 64 / wh);
		if (color == 0)
			s->img.data[c * s->win.x + x] = fade_color(s, s->tex.n[64 * s->tex.ty
				+ s->tex.tx], wdist);
		if (color == 1)
			s->img.data[c * s->win.x + x] = fade_color(s, s->tex.e[64 * s->tex.ty
				+ s->tex.tx], wdist);
		if (color == 2)
			s->img.data[c * s->win.x + x] = fade_color(s, s->tex.w[64 * s->tex.ty
				+ s->tex.tx], wdist);
		if (color == 3)
			s->img.data[c * s->win.x + x] = fade_color(s, s->tex.s[64 * s->tex.ty
				+ s->tex.tx], wdist);
	}
}

double				cast_single_ray(t_all *s, int x, int *wdir)
{
	double ray;
	double wdist;

	ray = (s->pos.th + s->win.fovh_2) - (x * s->win.a_p_pixel);
	if (get_wall_intersection(s, ray, wdir) == FALSE)
		return (INFINITY);
	wdist = l2dist(s->pos.x, s->pos.y, s->tex.wx, s->tex.wy);
	wdist *= cos(s->pos.th - ray);
	return (wdist);
}

int					get_wall_intersection(t_all *s, double ray, int *wdir)
{
	t_w w;

	w.xstep = 0;
	w.ystep = 0;
	w.xslope = 0;
	w.yslope = 0;
	w.nx = 0;
	w.ny = 0;
	w.f = 0;
	w.g = 0;
	w.hit = 0;
	w.hit_side = 0;
	w.mapx = 0;
	w.mapy = 0;
	s->w = w;
	s->w.xstep = sgn(cos(ray));
	s->w.ystep = sgn(sin(ray));
	get_wall_intersection2(s, ray, wdir);
	return (s->w.hit);
}

int					get_wall_intersection2(t_all *s, double ray, int *wdir)
{
	if (s->w.xstep == 0)
		s->w.xslope = INFINITY;
	else
		s->w.xslope = tan(ray);
	if (s->w.ystep == 0)
		s->w.yslope = INFINITY;
	else
		s->w.yslope = 1. / tan(ray);
	if (s->w.xstep > 0)
		s->w.nx = floor(s->pos.x) + 1;
	else
		s->w.nx = (s->w.xstep < 0 ? ceil(s->pos.x) - 1 : s->pos.x);
	if (s->w.ystep > 0)
		s->w.ny = floor(s->pos.y) + 1;
	else
		s->w.ny = (s->w.ystep < 0 ? ceil(s->pos.y) - 1 : s->pos.y);
	s->w.f = INFINITY;
	s->w.g = INFINITY;
	s->w.hit = FALSE;
	get_wall_intersection3(s, wdir, 0);
	return (s->w.hit);
}

void				get_wall_intersection3(t_all *s, int *wdir, int cell)
{
	while (!s->w.hit)
	{
		cell = get_wall_intersection4(s, 0, 0, 0);
		if (cell == 1)
		{
			if (s->w.hit_side == VERT)
			{
				*wdir = (s->w.xstep > 0) ? DIR_W : DIR_E;
				s->tex.wx = s->w.nx;
				s->tex.wy = s->w.f;
			}
			else
			{
				*wdir = (s->w.ystep > 0) ? DIR_S : DIR_N;
				s->tex.wx = s->w.g;
				s->tex.wy = s->w.ny;
			}
			s->w.hit = TRUE;
			break ;
		}
		if (s->w.hit_side == VERT)
			s->w.nx += s->w.xstep;
		else
			s->w.ny += s->w.ystep;
	}
}
