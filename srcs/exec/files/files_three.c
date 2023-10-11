/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:31:32 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/09 18:32:18 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_choose_redir(t_mini *minsh, int position, t_files *s_f)
{
	if ((minsh->cmds)[position].redir_type[s_f->i] == redir_left)
	{
		if (ft_redir_left(minsh, position, s_f) == 1)
			return (1);
	}
	else if ((minsh->cmds)[position].redir_type[s_f->i] == redir_double_left)
	{
		ft_redir_double_left(minsh, position, s_f);
	}
	else if ((minsh->cmds)[position].redir_type[s_f->i] == redir_right)
	{
		if (ft_redir_right(minsh, position, s_f) == 1)
			return (1);
	}
	else if ((minsh->cmds)[position].redir_type[s_f->i] == redir_double_right)
	{
		if (ft_redir_double_right(minsh, position, s_f) == 1)
			return (1);
	}
	return (0);
}

int	files(t_mini *minsh, int **fd_pipe, int position, int opt_exit)
{
	t_files	s_f;

	initialise_struct(&s_f, fd_pipe, opt_exit);
	while (s_f.i < (minsh->cmds)[position].redir)
	{
		if (ft_choose_redir(minsh, position, &s_f) == 1)
			return (1);
		s_f.i++;
	}
	ft_dup_fd(minsh, position, &s_f);
	return (0);
}
