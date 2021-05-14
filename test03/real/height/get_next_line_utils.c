/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:02:36 by psong             #+#    #+#             */
/*   Updated: 2021/05/13 11:01:43 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t				ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (src)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t src_len;
	size_t i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	while (src[i] != '\0' && dst_len + 1 + i < dstsize)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

char				*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (s1[tmp])
		tmp++;
	if (!(dst = (char *)malloc(sizeof(char) * (tmp + 1))))
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char				*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	len;

	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(dst = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strlcpy(dst, s1, (ft_strlen(s1) + 1));
	ft_strlcat(dst, s2, len);
	return (dst);
}
