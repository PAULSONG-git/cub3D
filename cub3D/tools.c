/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:29:56 by psong             #+#    #+#             */
/*   Updated: 2021/05/27 11:47:42 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					sprite_init(t_all *s)
{
	if (!(s->tex.zbuf = (double *)malloc(sizeof(double) * s->win.x)))
		return (-1);
	return (0);
}

int					ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int					ft_atoi(char *line, int *i)
{
	int				num;
	int				flag;

	num = 0;
	flag = 0;
	ft_spaceskip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
		flag = 1;
	}
	if (flag == 0)
		return (-1);
	return (num);
}

int					ft_strerror(int err)
{
	(err == -1) ? write(2, "Error : Couldn't open file (FD)\n", 32) : 0;
	(err == -3) ? write(2, "Error : Resolution specified twice\n", 35) : 0;
	(err == -4) ? write(2, "Error : Invalid resolution\n", 27) : 0;
	(err == -5) ? write(2, "Error : Floor/ceiling specified twice\n", 38) : 0;
	(err == -6) ? write(2, "Error : Invalid floor/ceiling line\n", 35) : 0;
	(err == -7) ? write(2, "Error : Texture path specified twice\n", 37) : 0;
	(err == -8) ? write(2, "Error : Malloc fail (texture path)\n", 35) : 0;
	(err == -9) ? write(2, "Error : Invalid texture image\n", 30) : 0;
	(err == -10) ? write(2, "Error : Invalid line in file\n", 29) : 0;
	(err == -11) ? write(2, "Error : Malloc fail (map table)\n", 32) : 0;
	(err == -12) ? write(2, "Error : Invalid map\n", 20) : 0;
	(err == -13) ? write(2, "Error : Map isn't a rectangle\n", 30) : 0;
	(err == -14) ? write(2, "Error : No resolution specified\n", 32) : 0;
	(err == -15) ? write(2, "Error : Missing texture\n", 24) : 0;
	(err == -16) ? write(2, "Error : Missing floor/ceiling color\n", 26) : 0;
	(err == -17) ? write(2, "Error : No starting position\n", 29) : 0;
	(err == -18) ? write(2, "Error : Multiple starting positions\n", 36) : 0;
	(err == -19) ? write(2, "Error : Map isn't surrounded by walls\n", 38) : 0;
	return (-1);
}

double
get_luminosity(t_all *s, double dist)
{
    double Dist = -1;
    if( Dist < 0 )
		Dist = (s->map.x + s->map.y) / 2.0;
    return ((dist > Dist) ? 0 : (1. - dist/Dist));
}

int				fade_color(t_all *s, int color, double dist)
{
	double lum = get_luminosity(s, dist);
    if( lum < 0 ) lum = 0;
    else if( lum > 1 ) lum = 1;
    int r, g, b = 0x00000000;
    decode_color(color, &r, &g, &b);
    return encode_color((int)(r*lum), (int)(g*lum), (int)(b*lum));
}

void			decode_color(int color, int *r, int *g, int *b)
{
	*r = color / 256 / 256; // red 추출
	*g = color / 256 % 256; // green 추출
	*b = (color % 256); // blue 추출
}

int				encode_color(int r, int g, int b)
{
	int color;

	color = r * 256 *256 + g * 256 + b;
	return(color);
}
