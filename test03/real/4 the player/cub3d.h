#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF


#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
static const double FOVH_2 = FOV_H / 2.0;


#define  WALL_H		1.0

#define  _2PI       6.28318530717958647692  /* 2 * M_PI */

#define  ROT_UNIT   0.03    /* rad */
#define  MOVE_UNIT  0.1

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17 //exit key code

#define KEY_ESC			53
#define KEY_Q			12
#define KEY_W			13
#define KEY_E			14
#define KEY_R			15
#define KEY_A			0
#define KEY_S			1
#define KEY_D			2
#define KEY_LEFT 		123
#define KEY_RIGHT 		124
#define texWidth 64
#define texHeight 64

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
	double			ANGLE_PER_PIXEL;
	double			FOV_V;	
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}				t_img;
/*
typedef struct	s_err
{
	int				n;
	int				m;
	int				p;
}				t_err;
*/
typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	//int			spr;
}				t_map;
/*
typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;

}				t_tex;
*/
typedef struct	s_pos
{
	double			x;
	double			y;
	double			th;
}				t_pos;
/*
typedef struct	s_dir
{
	double			x;
	double			y;
	double			a;
}				t_dir;

typedef struct	s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
}				t_ray;

typedef struct	s_hit
{
	double			wx;
	double			wy;
	int				tx;
	int				ty;
	double			d;
}				t_hit;

typedef struct	s_spr
{
	double			x;
	double			y;
	double			d;
}				t_spr;

typedef struct	s_stk
{
	double			x;
	double			y;
	double			d;
}				t_stk;
*/
typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
//	t_err			err;
	t_map			map;
//	t_tex			tex;
	t_pos			pos;
//	t_dir			dir;
//	t_ray			ray;
//	t_hit			hit;
//	t_spr			*spr;
//	t_stk			*stk;
}				t_all;

enum { VERT, HORIZ };

typedef enum { false=0, true=1 } bool;
typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

void			ft_init(char *cub, int bmp);
void			ft_declare(t_all s, char *cub, int bmp);
int				ft_cubed(t_all s, char *cub, int bmp);
void			ft_draw(t_all *s);

int				ft_parse(t_all *s, char *cub);
int				ft_line(t_all *s, char *line);

int				ft_map(t_all *s, char *line, int *i);
char			*ft_slab(t_all *s, char *line, int *i);
int				ft_slablen(t_all *s, char *line);
int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i);
int				ft_xpm(t_all *s, unsigned int **adr, char *file);

int				ft_slist(t_all *s);
void			ft_pos(t_all *s);
int				ft_colors(unsigned int *color, char *line, int *i);
int				ft_res(t_all *s, char *line, int *i);

int				ft_parcheck(t_all *s);
int				ft_mapcheck(t_all *s);
int				ft_savecheck(char *arg, char *save);
int				ft_namecheck(char *arg, char *ext);

int				ft_key(int key, void *arg);
void			ft_rotate(t_all *s, double c);
void			ft_strafe(t_all *s, double c);
void			ft_move(t_all *s, double c);
int				ft_close(t_all *s, int win);

void			ft_screen(t_all *s);
void			ft_ray(t_all *s);
void			ft_dir(t_all *s);
void			ft_ver(t_all *s);
void			ft_hor(t_all *s);

void			ft_stock(t_all *s);
int				ft_size(t_all *s);
void			ft_column(t_all *s, int start);
unsigned int	ft_pixel(t_all *s, double i);

void			ft_sprite(t_all *s);
void			ft_sorder(t_all *s);
void			ft_slocate(t_all *s, double dirx, double diry, double dist);
void			ft_sdraw(t_all *s, int loc, double dist);
unsigned int	ft_spixel(t_all *s, int index, unsigned int col);

int				ft_bitmap(t_all *s);
void			ft_bdraw(t_all *s);
void			ft_bfile(t_all *s, int fd);
void			ft_binfo(t_all *s, int fd);
void			ft_bdata(t_all *s, int fd);

int				ft_atoi(char *line, int *i);
int				ft_spaceskip(char *line, int *i);
int				ft_strerror(int err);

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dest, const char *src, size_t dstsize);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);

int				map_get_cell(t_all *s, int x, int y );
int				sgn( double d );
double			l2dist( double x0, double y0, double x1, double y1 );
double			cast_single_ray(t_all *s, int x, dir_t *wdir);
bool			get_wall_intersection(t_all *s, double ray, double px, double py, dir_t* wdir, double* wx, double* wy );
int				get_wall_height(t_all *s, double dist );
void			draw_wall(t_all *s, double wdist, int x, int color);
void			render( t_all *s );
int				key_press(int key, t_all *s);
void			player_rotate( t_all *s, double th );
static int		get_move_offset( double th, int key, double amt, double* pdx, double* pdy );
int				player_move( t_all *s, int key, double amt );



#endif
