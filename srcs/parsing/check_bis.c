/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:42:51 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/04 16:44:24 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_dir(t_mini *mini, int pos)
{
	struct stat	s;
	char		*str;

	if (stat(mini->cmds[pos].cmd[0], &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
			str = ft_strjoin(mini->cmds[pos].cmd[0], ": is a directory\n");
			print_error(str);
			free(str);
			free_t_mini(mini);
			exit(126);
		}
	}
	return (1);
}
