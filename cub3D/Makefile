NAME		= cub3D
CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror
LXFLAGS 	= -lmlx -framework OpenGL -framework AppKit
MLX			= ../mlx
RM 				= rm -f
SRCS 		= ./cub3d.c ./parse.c ./parse_map.c ./parse_tools.c ./parse_check.c ./get_next_line.c ./get_next_line_utils.c  ./key.c ./sprite.c ./bitmap.c ./tools.c ./wall.c ./wall_tool.c ./wall_tool2.c

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) -g3 -fsanitize=address $(CFLAGS) -L $(MLX) $(LXFLAGS) $(SRCS)
	./cub3D map.cub

clean:
	$(RM) bitmap.bmp

fclean: clean
	$(RM) $(NAME)

re: fclean all
