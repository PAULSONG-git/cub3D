#include "cub3d.h"

int		ft_namecheck(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_savecheck(char *arg, char *save)
{
	int	i;

	i = 0;
	while (arg[i] == save[i])
	{
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_mapcheck(t_all *s)
{
	int a = 0;
	int b = 0;
	int c = 0;
	while (a < s->map.x)
	{
		while (b < s->map.l)
		{
			if (!(s->map.tab[a][b] == '1' || s->map.tab[a][b] == ' '))
			{
				if (s->map.tab[a][b+1] == ' ')
					c = 1;	
				if (b > 0)
				{
					if (s->map.tab[a][b-1] == ' ')
						c = 1;
					if (a > 0)
						if(s->map.tab[a-1][b-1] == ' ')
							c = 1;
				}
				if (a < s->map.x - 1)
				{
					if (s->map.tab[a+1][b] == ' ')
						c = 1;
					if (b > 0)
						if (s->map.tab[a+1][b-1] == ' ')
							c = 1;
					if (s->map.tab[a+1][b+1] == ' ')
						c = 1;
				}
				if (a > 0)
				{
					if (s->map.tab[a-1][b] == ' ')
						c = 1;
					if (s->map.tab[a-1][b+1] == ' ')
						c = 1;
				}
				if (a == 0 || a == s->map.x -1 || b == 0 || b == s->map.l -1)
					c = 1;
			}
			b++;
		}
		b = 0;
		a++;
	}
	return (c == 1 ? -1 : 0 );
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (ft_strerror(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (ft_strerror(-16));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));
	return (1);
}
