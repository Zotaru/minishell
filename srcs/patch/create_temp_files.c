/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_temp_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 03:37:47 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 21:23:05 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temp_files_for_cmd(t_mini *minsh, int position, t_cmd *act_cmd)
{
	int	pos[3];

	pos[0] = position;
	pos[1] = 0;
	pos[2] = 0;
	while (pos[1] < act_cmd->redir)
	{
		if ((act_cmd->redir_type)[pos[1]] == redir_left
			|| (act_cmd->redir_type)[pos[1]] == redir_double_left)
		{
			if ((act_cmd->redir_type)[pos[1]] == redir_double_left)
				here_doc(act_cmd, pos, minsh);
			pos[2]++;
		}
		pos[1]++;
	}
	return ;
}

void	create_temp_files(t_mini *minsh)
{
	int	position;

	position = 0;
	while (position < minsh->nb_cmd)
	{
		temp_files_for_cmd(minsh, position, &((minsh->cmds)[position]));
		position++;
	}
	return ;
}
