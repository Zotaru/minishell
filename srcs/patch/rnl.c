/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:54:54 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/05 13:58:18 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_buffer(int fd, char *buffer, int *start, int *end)
{
	*start = 0;
	*end = read(fd, buffer, 4096);
	if (*end <= 0)
		return (0);
	return (1);
}

static char	*copy_line(char *buffer, int *start, int end)
{
	char	*line;
	int		i;

	line = malloc(end - *start + 1);
	if (!line)
		return ((char *)0);
	i = *start;
	while (i < end)
	{
		line[i - *start] = buffer[i];
		i++;
	}
	line[i - *start] = '\0';
	*start = end + 1;
	return (line);
}

char	*read_next_line(int fd)
{
	static char	buffer[4096];
	static int	start;
	static int	end;
	int			i;

	if (fd < 0 || (start == end && !read_buffer(fd, buffer, &start, &end)))
		return ((char *)0);
	i = start;
	while (i < end)
	{
		if (buffer[i] == '\n')
			return (copy_line(buffer, &start, i));
		i++;
	}
	start = i;
	return ((char *)0);
}
