/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 04:01:47 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 21:53:23 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_empty_cmd_from_env(t_mini *minsh, int position)
{
	if (minsh->cmds[position].cmd[0][0] == 0)
	{
		if (minsh->cmds[position].token[0][0] == '$')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ctrlc(int signal)
{
	extern int	g_status;

	g_status = 130;
	printf("\n");
	(void)signal;
}

void	ctrl_backslash(int signal)
{
	extern int	g_status;

	g_status = 131;
	printf("Quit (core dumped)\n");
	(void)signal;
}

void	child(t_mini *minsh, int **fd_pipe, int position)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	files(minsh, fd_pipe, position, 1);
	close(fd_pipe[0][0]);
	close(fd_pipe[0][1]);
	if (fd_pipe[1][0] != 0)
		close(fd_pipe[1][0]);
	clear_double_tab_int(fd_pipe, 2);
	if (minsh->cmds[position].cmd)
	{
		if (!ft_empty_cmd_from_env(minsh, position)
			&& minsh->cmds[position].cmd[0][0] == 0)
			err_cmd_not_found(minsh, &(minsh->cmds[position]));
	}
	if ((minsh->cmds)[position].cmd != NULL)
		if ((minsh->cmds)[position].cmd[0] != NULL
			&& ft_check_dir(minsh, position)
			&& !ft_empty_cmd_from_env(minsh, position))
			cmds(minsh, position);
	free_t_mini(minsh);
	exit(EXIT_SUCCESS);
}
