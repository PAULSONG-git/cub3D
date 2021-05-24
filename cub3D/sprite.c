/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:46:21 by psong             #+#    #+#             */
/*   Updated: 2021/05/24 17:54:25 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					cmp_sprites(const void *a, const void *b)
{
	return (((const t_spr*)a)->dist > ((const t_spr*)b)->dist) ? -1 : 1;
}

void				get_visible_sprites(t_all *s, int *pcnt, int x, int y)
{
	int				n;
	t_spr			*sp;

	sp = NULL;
	s->spr = sp;
	n = 0;
	while (++x < s->map.x)
	{
		while (++y < s->map.y)
		{
			if (map_get_cell(s, x, y) <= 1)
				continue;
			if (n == 0)
				s->spr = (t_spr*)malloc(sizeof(t_spr));
			else
				s->spr = (t_spr*)realloc(s->spr, sizeof(t_spr) * (n + 1));
			get_visible_sprites2(s, n, x, y);
			n++;
		}
		y = -1;
	}
	*pcnt = n;
}

void				get_visible_sprites2(t_all *s, int n, int x, int y)
{
	s->spr[n].tex = map_get_cell(s, x, y) + 2;
	s->spr[n].x = x;
	s->spr[n].y = y;
	s->spr[n].th = atan2((y + 0.5) - (s->pos.y), (x + 0.5) - (s->pos.x));
	if (s->spr[n].th < 0)
		s->spr[n].th += TWOPI;
	s->spr[n].dist = l2dist(s->pos.x, s->pos.y, x + 0.5, y + 0.5)
		* cos(s->pos.th - s->spr[n].th);
}

void				draw_sprites(t_all *s)
{
	int				nsp;
	int				i;
	int				cx;
	int				sh;
	double			angle;

	nsp = 0;
	i = -1;
	get_visible_sprites(s, &nsp, -1, -1);
	qsort(s->spr, nsp, sizeof(t_spr), cmp_sprites);
	while (++i < nsp)
	{
		sh = get_wall_height(s, s->spr[i].dist);
		angle = s->spr[i].th - s->pos.th;
		if (angle > M_PI)
			angle -= TWOPI;
		else if (angle < -M_PI)
			angle += TWOPI;
		cx = (int)((s->win.fovh_2 - angle) * s->win.p_p_angle);
		draw_sprites2(s, cx, sh, i);
	}
	if (nsp > 0)
		free(s->spr);
}

void				draw_sprites2(t_all *s, int cx, int sh, int i)
{
	int				xmin;
	int				y0;
	int				y;
	int				ty;
	double			txratio;

	xmin = max(0, cx - sh / 2) - 1;
	while (++xmin < min(s->win.x, cx + sh / 2))
	{
		if (s->spr[i].dist > s->tex.zbuf[xmin])
			continue;
		if (s->spr[i].dist < 0.3)
			continue;
		txratio = (double)(xmin - cx) / sh + 0.5;
		y0 = (int)((s->win.y - sh) / 2.0);
		y = max(0, y0) - 1;
		while (++y < min(s->win.y, y0 + sh))
		{
			ty = (int)((double)(y - y0) * 64 / sh);
			if ((s->tex.i[64 * ty + (int)(txratio * 64)] & 0x00ffffff) != 0)
				s->img.data[y * s->win.x + xmin] =
					s->tex.i[64 * (ty) + ((int)(txratio * 64))];
		}
	}
}
