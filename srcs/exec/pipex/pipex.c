/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 03:46:59 by alex              #+#    #+#             */
/*   Updated: 2023/09/04 18:11:52 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipe_wait(int nb_cmd, int **fd_pipe, int *pid)
{
	int			i;
	int			status;
	extern int	g_status;

	i = 0;
	status = 0;
	if (fd_pipe[1][0] > 0)
		close(fd_pipe[1][0]);
	clear_double_tab_int(fd_pipe, 2);
	while (i < nb_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		i++;
	}
	return ;
}

int	check_hd(t_mini *minsh, int position)
{
	int	i;

	i = 0;
	while (i < minsh->cmds[position].redir)
	{
		if (minsh->cmds[position].redir_type[i] == redir_double_left)
			return (1);
		i++;
	}
	return (0);
}

int	**init_pipes(void)
{
	int	**pfd;

	pfd = malloc(sizeof(int *) * 2);
	pfd[0] = malloc(sizeof(int) * 2);
	pfd[1] = malloc(sizeof(int) * 2);
	pfd[0][0] = -1;
	pfd[0][1] = -1;
	pfd[1][0] = 0;
	pfd[1][1] = 1;
	return (pfd);
}

void	ft_else(t_mini *minsh, int **pfd, int i, int *pid)
{
	extern int	g_status;
	int			status;

	close(pfd[1][1]);
	if (pfd[1][0] > 0)
		close(pfd[1][0]);
	pfd[1][0] = pfd[0][0];
	if (check_hd(minsh, i) == 1)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
}

void	pipex(t_mini *minsh, int *pid)
{
	int			i;
	int			**pfd;

	pfd = init_pipes();
	i = -1;
	while (++i < minsh->nb_cmd)
	{
		if (pipe(pfd[0]))
			ft_pipex_error(pfd, minsh);
		pfd[1][1] = pfd[0][1];
		pid[i] = fork();
		signal(SIGINT, ctrlc);
		signal(SIGQUIT, ctrl_backslash);
		if (pid[i] == 0)
		{
			free(pid);
			child(minsh, pfd, i);
			exit(0);
		}
		else
			ft_else(minsh, pfd, i, pid);
	}
	close_pipe_wait(minsh->nb_cmd, pfd, pid);
	return ;
}
