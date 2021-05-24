#include "cub3d.h"

int
map_get_cell(t_all *s, int x, int y )
{
	char c;
	int  n;

	n = 0;
	c = s->map.tab[x][y];
	if (c == '1')
		n = 1;
	else if (c == '2')
		n = 2;
	return ((x >= 0 && x < s->map.x && y >= 0 && y < s->map.y) ? n : -1);
}

int
sgn( double d )
{
	if (fabs(d) < (1e-06))
		d = 0;
    return d == 0 ? 0 : ((d > 0) ? 1 : -1);
}

double
l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

double	deg2rad(double d)
{
	d = d * M_PI/180.0;
	return (d);
}

double  rad2deg(double d)
{
	d = d * 180.0/M_PI;
	return (d);
}

double	min(double a, double b)
{
	if (b > a)
		return (a);
	return (b);
}

double  max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
