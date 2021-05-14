#include "cub3d.h"

int		main(int ac, char **av)
{
	if (ac == 2 && ft_namecheck(av[1], "cub"))
		ft_init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
