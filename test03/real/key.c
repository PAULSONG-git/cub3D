#include "cub3d.h"

int		ft_close(t_all *s, int win)
{
	int	i;

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

int				key_press(int key, t_all *s)
{
	static int a = 0;

	if(key == KEY_ESC )
		exit(0);
	if( key == KEY_LEFT || key == KEY_RIGHT ) {
            player_rotate(s, ROT_UNIT * (key==KEY_LEFT ? 1 : -1));
			ft_draw(s);
        }
    else if( key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D ) {
            if( player_move(s, key, MOVE_UNIT) == 0 ) {
			ft_draw(s);
            }
	}
	return (0);
}

void
player_rotate( t_all* s, double th )
{
    s->pos.th += th;
    if( s->pos.th < 0 ) s->pos.th += _2PI;
    else if( s->pos.th > _2PI ) s->pos.th -= _2PI;
}

static int
get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
		default: /* invalid */
            return -1;
    }
    return 0;
}

int
player_move( t_all *s, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(s->pos.th, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = s->pos.x + dx;
    ny = s->pos.y + dy;

    if( map_get_cell(s, (int)nx, (int)ny) != 0) {
        printf("** bump !\n");
        return -1;
    }
    s->pos.x = nx;
    s->pos.y = ny;
    return 0;
}
