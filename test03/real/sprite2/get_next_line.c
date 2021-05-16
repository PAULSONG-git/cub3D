/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:59:54 by psong             #+#    #+#             */
/*   Updated: 2021/05/13 11:01:32 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int					split(char **backup, char **line, int idx)
{
	char			*temp1;
	char			*temp2;

	(*backup)[idx] = '\0';
	if (!(temp1 = ft_strdup(*backup)))
		return (-1);
	if (!(temp2 = ft_strdup(*backup + idx + 1)))
	{
		free(temp1);
		temp1 = NULL;
		return (-1);
	}
	*line = temp1;
	free(*backup);
	*backup = temp2;
	return (1);
}

int					remain(char **backup, char **line, int end)
{
	int				idx;

	if (end == -1)
		return (-1);
	if (*backup && (idx = ft_strchr(*backup, '\n')) >= 0)
		return (split(backup, line, idx));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;
	int				end;
	int				idx;

	if ((fd < 0) || (fd > OPEN_MAX) || (line == NULL) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((end = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[end] = '\0';
		tmp = backup[fd];
		backup[fd] = ft_strjoin(backup[fd], buf);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if ((idx = ft_strchr(backup[fd], '\n')) >= 0)
			return (split(&backup[fd], line, idx));
	}
	return (remain(&backup[fd], line, end));
}
