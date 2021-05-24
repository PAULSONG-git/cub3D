/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:47:58 by psong             #+#    #+#             */
/*   Updated: 2021/05/24 13:47:59 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i);
	if ((line[i] == '1') && line[i] != '\0')
		s->err.n = ft_map(s, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = ft_res(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.c, line, &i);
	if (ft_spaceskip(line, &i) && s->err.n == 0 && line[i] != '\0')
		return (ft_strerror(-10));
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0);
}

int		ft_parse(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (ft_strerror(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	map_extend(s, 0, 0);
	ft_pos(s, -1, -1, 0);
	if (ret == -1)
		return (ft_strerror(ret + 1));
	return (ft_parcheck(s));
}
