/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_tmp_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 05:18:10 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 21:32:47 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_file(t_mini *minsh, t_cmd *act_cmd, int position_inf)
{
	if (ft_strncmp((act_cmd->input_file)[position_inf], "/tmp/rand", 9) == 0)
	{
		if (unlink((act_cmd->input_file)[position_inf]) == -1)
		{
			perror((act_cmd->input_file)[position_inf]);
			free_t_mini(minsh);
			exit(1);
		}
	}
}

void	unlink_all_hd_files(t_mini *minsh, t_cmd *act_cmd)
{
	int	position_redir;
	int	position_inf;

	position_redir = 0;
	position_inf = 0;
	while (position_redir < act_cmd->redir)
	{
		if ((act_cmd->redir_type)[position_redir] == redir_left
			|| (act_cmd->redir_type)[position_redir] == redir_double_left)
		{
			if ((act_cmd->redir_type)[position_redir] == redir_double_left)
				unlink_file(minsh, act_cmd, position_inf);
			position_inf++;
		}
		position_redir++;
	}
}

void	send_act_cmd_for_unlink(t_mini *minsh)
{
	int	position;

	position = 0;
	while (position < minsh->nb_cmd)
	{
		unlink_all_hd_files(minsh, &((minsh->cmds)[position]));
		position++;
	}
}
