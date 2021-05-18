#include "cub3d.h"

int		errorcheck2(t_all *s)
{
	if ((s->err.R == 0 || s->err.NO == 0 || s->err.SO == 0) || (s->err.WE == 0 || s->err.EA == 0) || (s->err.S == 0 || s->err.F == 0 || s->err.C == 0))
	{	
		printf("Missing component");
		return (1);
	}
	if (s->err.p != 1)
	{
		printf("wrong starting position");
		return (1);
	}
	return (0);
}

void		errorcheck1(t_all *s, int type)
{
	if (type == 1)
		(s->err.R == 1 ? ft_strerror(-14) : (s->err.R = 1));
	else if (type == 2)
		(s->err.NO == 1 ? ft_strerror(-14) : (s->err.NO = 1));
	else if (type == 3)
		(s->err.SO == 1 ? ft_strerror(-14) : (s->err.SO = 1));
	else if (type == 4)
		(s->err.WE == 1 ? ft_strerror(-14) : (s->err.WE = 1));
	else if (type == 5)
		(s->err.EA == 1 ? ft_strerror(-14) : (s->err.EA = 1));
	else if (type == 6)
		(s->err.S == 1 ? ft_strerror(-14) : (s->err.S = 1));
	else if (type == 7)
		(s->err.F == 1 ? ft_strerror(-14) : (s->err.F = 1));
	else if (type == 8)
		(s->err.C == 1 ? ft_strerror(-14) : (s->err.C = 1));
}

int		ft_res(t_all *s, char *line, int *i)
{
	if (s->win.x != 0 || s->win.y != 0)
		return (-3);
	(*i)++;
	s->win.x = ft_atoi(line, i);
	s->win.y = ft_atoi(line, i);
	if (s->win.x > 2560)
		s->win.x = 2560;
	if (s->win.y > 1400)
		s->win.y = 1400;
	ft_spaceskip(line, i);
	if (s->win.x <= 0 || s->win.y <= 0 || line[*i] != '\0')
		return (-4);
	return (0);
}

int		ft_colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = ft_atoi(line, i);
	if (line[*i] != ',')
		return (-6);
		(*i)++;
	g = ft_atoi(line, i);
	if (line[*i] != ',')
		return (-6);
			(*i)++;
	b = ft_atoi(line, i);
	ft_spaceskip(line, i);
	if (!(line[*i] == '\0' && (0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255)))
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

void	ft_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;
	double  th;

	i = -1;
	j = -1;
	while (++i < s->map.x)
	{
		while (++j < s->map.y)
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.x = (double)i + 0.5;
				s->pos.y = (double)j + 0.5;
				if (c == 'E')
					th = 0;
				else if (c == 'N')
					th = 90;
				else if (c == 'W')
					th = 180;
				else if (c == 'S')
					th = 240;
				s->pos.th = deg2rad(th);
				s->err.p++;
			}
		}
		j = -1;
	}
}
/*
int		ft_slist(t_all *s)
{
	int		i;
	int		j;
	int		k;

	if (s->spr != NULL)
		free(s->spr);
	if (!(s->spr = malloc(sizeof(t_spr) * s->map.spr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (s->map.tab[j][k] == '2')
			{
				s->spr[i].y = (double)j + 0.5;
				s->spr[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}
*/
