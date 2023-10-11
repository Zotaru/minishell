/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:28:19 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 21:57:26 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_double_right(t_mini *minsh, int position, t_files *s_f)
{
	if (s_f->fd_outfile > 0)
		close(s_f->fd_outfile);
	if (ft_strncmp("/dev/stdout", \
	(minsh->cmds)[position].output_file[s_f->position_outfile], 12) == 0)
		s_f->opt_stdout = 1;
	else
		s_f->opt_stdout = 0;
	s_f->fd_outfile = \
	open((minsh->cmds)[position].output_file[s_f->position_outfile], \
	O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (s_f->fd_outfile < 0)
		return (err_bis(minsh, s_f, position));
	s_f->position_outfile++;
	return (0);
}

void	dup_one(t_mini *minsh, int position, t_files *s_f)
{
	if ((minsh->cmds)[position].redir_in > 0)
	{
		if (s_f->opt_exit == 1)
			dup2(s_f->fd_infile, STDIN_FILENO);
		close(s_f->fd_infile);
	}
	else
	{
		if (s_f->fd_pipe != NULL)
			if (s_f->opt_exit == 1)
				dup2((s_f->fd_pipe)[1][0], STDIN_FILENO);
	}
}

void	dup_two(t_mini *minsh, int position, t_files *s_f)
{
	if ((minsh->cmds)[position].redir_out > 0 && !isatty(s_f->fd_outfile))
	{
		if (s_f->opt_exit == 1)
			dup2(s_f->fd_outfile, STDOUT_FILENO);
	}
	else if (position < (minsh->nb_cmd - 1) && s_f->fd_pipe != NULL)
	{
		if (s_f->opt_exit == 1)
			dup2((s_f->fd_pipe)[1][1], STDOUT_FILENO);
	}
	if ((minsh->cmds)[position].redir_out > 0)
		close(s_f->fd_outfile);
}

int	ft_dup_fd(t_mini *minsh, int position, t_files *s_f)
{
	dup_one(minsh, position, s_f);
	dup_two(minsh, position, s_f);
	return (0);
}

void	initialise_struct(t_files *s_f, int **fd_pipe, int opt_exit)
{
	s_f->position_infile = 0;
	s_f->position_outfile = 0;
	s_f->i = 0;
	s_f->fd_infile = -1;
	s_f->fd_outfile = -1;
	s_f->fd_pipe = fd_pipe;
	s_f->opt_exit = opt_exit;
	s_f->opt_stdout = 0;
}
