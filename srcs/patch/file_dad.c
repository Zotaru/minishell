/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:10:12 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 21:28:07 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temp_files_for_dad(t_mini *minsh, int position, t_cmd *act_cmd)
{
	int		pos[3];
	char	*name;

	pos[0] = position;
	pos[1] = 0;
	pos[2] = 0;
	while (pos[1] < act_cmd->redir)
	{
		if ((act_cmd->redir_type)[pos[1]] == redir_left
			|| (act_cmd->redir_type)[pos[1]] == redir_double_left)
		{
			if ((act_cmd->redir_type)[pos[1]] == redir_double_left)
			{
				name = create_random_name(minsh, pos);
				free(((minsh->cmds)[pos[0]]).input_file[pos[2]]);
				((minsh->cmds)[pos[0]]).input_file[pos[2]] = name;
			}
			pos[2]++;
		}
		pos[1]++;
	}
	return ;
}

void	create_file_for_dad(t_mini *minsh)
{
	int	position;

	position = 0;
	while (position < minsh->nb_cmd)
	{
		temp_files_for_dad(minsh, position, (&((minsh->cmds)[position])));
		position++;
	}
	return ;
}
