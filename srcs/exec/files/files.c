/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:25:29 by amonier           #+#    #+#             */
/*   Updated: 2023/09/16 21:58:23 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_left(t_mini *minsh, int position, t_files *s_f)
{
	if (s_f->fd_infile > 0)
		close(s_f->fd_infile);
	s_f->fd_infile = \
	open((minsh->cmds)[position].input_file[(s_f->position_infile)], O_RDONLY);
	if (s_f->fd_infile < 0)
	{
		perror((minsh->cmds)[position].input_file[(s_f->position_infile)]);
		if (s_f->opt_exit == 1)
		{
			if (s_f->fd_pipe != NULL)
			{
				close((s_f->fd_pipe)[0][0]);
				close((s_f->fd_pipe)[0][1]);
				clear_double_tab_int(s_f->fd_pipe, 2);
			}
			free_t_mini(minsh);
			exit(1);
		}
		else
			return (1);
	}
	(s_f->position_infile)++;
	return (0);
}

int	ft_redir_double_left(t_mini *minsh, int position, t_files *s_f)
{
	if (s_f->fd_infile > 0)
		close(s_f->fd_infile);
	s_f->fd_infile = \
		open((minsh->cmds)[position].input_file[(s_f->position_infile)], \
		O_RDONLY);
	if (s_f->fd_infile < 0)
	{
		perror((minsh->cmds)[position].input_file[(s_f->position_infile)]);
		if (s_f->opt_exit == 1)
		{
			if (s_f->fd_pipe != NULL)
			{
				close((s_f->fd_pipe)[0][0]);
				close((s_f->fd_pipe)[0][1]);
				clear_double_tab_int(s_f->fd_pipe, 2);
			}
			free_t_mini(minsh);
			exit(1);
		}
		else
			return (1);
	}
	s_f->position_infile++;
	return (0);
}

int	err_outfile(t_mini *minsh, int position, t_files *s_f)
{
	perror((minsh->cmds)[position].output_file[s_f->position_outfile]);
	if (s_f->opt_exit == 1)
	{
		if (s_f->fd_pipe != NULL)
		{
			close((s_f->fd_pipe)[0][0]);
			close((s_f->fd_pipe)[0][1]);
			clear_double_tab_int((s_f->fd_pipe), 2);
		}
		free_t_mini(minsh);
		exit(1);
	}
	else
		return (1);
}

int	ft_redir_right(t_mini *minsh, int position, t_files *s_f)
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
	O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (s_f->fd_outfile < 0)
		return (err_outfile(minsh, position, s_f));
	s_f->position_outfile++;
	return (0);
}

int	err_bis(t_mini *minsh, t_files *s_f, int position)
{
	perror((minsh->cmds)[position].output_file[s_f->position_outfile]);
	if (s_f->opt_exit == 1)
	{
		if (s_f->fd_pipe != NULL)
		{
			close((s_f->fd_pipe)[0][0]);
			close((s_f->fd_pipe)[0][1]);
			clear_double_tab_int((s_f->fd_pipe), 2);
		}
		free_t_mini(minsh);
		exit(1);
	}
	else
		return (1);
}
