/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 20:40:31 by psong             #+#    #+#             */
/*   Updated: 2021/05/24 20:45:19 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					map_get_cell(t_all *s, int x, int y)
{
	char				c;
	int					n;

	n = 0;
	c = s->map.tab[x][y];
	if (c == '1')
		n = 1;
	else if (c == '2')
		n = 2;
	return ((x >= 0 && x < s->map.x && y >= 0 && y < s->map.y) ? n : -1);
}

int					sgn(double d)
{
	if (fabs(d) < (1e-06))
		d = 0;
	if (d == 0)
		d = 0;
	else
	{
		if (d > 0)
			d = 1;
		else
			d = -1;
	}
	return (d);
}

double				l2dist(double x0, double y0, double x1, double y1)
{
	double dx;
	double dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

double				deg2rad(double d)
{
	d = d * M_PI / 180.0;
	return (d);
}

double				rad2deg(double d)
{
	d = d * 180.0 / M_PI;
	return (d);
}
