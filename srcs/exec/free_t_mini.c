/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:01:32 by amonier           #+#    #+#             */
/*   Updated: 2023/08/09 17:17:54 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_cmd(t_cmd *macmd)
{
	if (macmd->cmd != NULL)
		free_double_tab_char(macmd->cmd);
	if (macmd->path != NULL)
		free(macmd->path);
	if (macmd->input_file != NULL)
		free_double_tab_char(macmd->input_file);
	if (macmd->output_file != NULL)
		free_double_tab_char(macmd->output_file);
	if (macmd->token != NULL)
		free(macmd->token);
	if (macmd->redir_type != NULL)
		free(macmd->redir_type);
	return ;
}

void	free_t_mini(t_mini *minsh)
{
	ft_clean_split(minsh->envp);
	ft_free_cmds(minsh->nb_cmd, minsh);
	return ;
}

void	free_t_mini_export(t_mini *minsh, int size_env)
{
	free_double_tab_char_export(minsh->envp, size_env);
	ft_free_cmds(minsh->nb_cmd, minsh);
	return ;
}
