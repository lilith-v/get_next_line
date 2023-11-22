/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:26:48 by livardan          #+#    #+#             */
/*   Updated: 2021/02/21 12:23:24 by livardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*fline(char *remind)
{
	int		i;
	char	*str;

	i = 0;
	if (!remind)
		return (0);
	while (remind[i] && remind[i] != '\n')
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (remind[i] && remind[i] != '\n')
	{
		str[i] = remind[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*fremind(char *remind)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!remind)
		return (0);
	while (remind[i] && remind[i] != '\n')
		i++;
	if (!remind[i])
	{
		free(remind);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * ((ft_strlen(remind) - i) + 1))))
		return (0);
	i++;
	while (remind[i])
		str[j++] = remind[i++];
	str[j] = '\0';
	free(remind);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char		*remind;
	int				rd;
	char			*buf;

	rd = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!katox(remind) && rd != 0)
	{
		if ((rd = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[rd] = '\0';
		remind = ft_strjoin(remind, buf);
	}
	free(buf);
	*line = fline(remind);
	remind = fremind(remind);
	if (rd == 0)
		return (0);
	return (1);
}
