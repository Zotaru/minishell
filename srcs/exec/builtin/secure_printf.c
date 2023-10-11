/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:24:05 by alex              #+#    #+#             */
/*   Updated: 2023/08/09 18:18:36 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_writable(char *file, t_mini *minsh)
{
	int		fd;

	fd = open(file, O_WRONLY);
	if (fd == -1)
	{
		perror(file);
		free_t_mini(minsh);
		exit(errno);
	}
	if (write(fd, "", 0) == -1)
	{
		close(fd);
		perror(file);
		free_t_mini(minsh);
		exit(errno);
	}
	close(fd);
}

void	secure_printf(t_mini *minsh, int position, char *str, int nl)
{
	int		len;

	len = ft_split_len((minsh->cmds)[position].output_file) - 1;
	if (len > 0)
		is_writable((minsh->cmds)[position].output_file[len], minsh);
	printf("%s", str);
	if (nl == 1)
		printf("\n");
}
