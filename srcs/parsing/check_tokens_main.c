/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:31:11 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/28 14:27:26 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_type(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	cmd->redir_type = malloc(sizeof(int) * (cmd->redir + 1));
	if (!cmd->redir_type)
		return ;
	while (cmd->token[++i])
	{
		if (!ft_strncmp(cmd->token[i], REDIR_DOUBLE_LEFT, 2))
			cmd->redir_type[j++] = redir_double_left;
		else if (!ft_strncmp(cmd->token[i], REDIR_DOUBLE_RIGHT, 2))
			cmd->redir_type[j++] = redir_double_right;
		else if (!ft_strncmp(cmd->token[i], REDIR_LEFT, 1))
			cmd->redir_type[j++] = redir_left;
		else if (!ft_strncmp(cmd->token[i], REDIR_RIGHT, 1))
			cmd->redir_type[j++] = redir_right;
	}
	cmd->redir_type[j] = 0;
}

void	ft_check_elements(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->p = 0;
	cmd->token = (char **)malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!cmd->token)
		return ;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_quote(line, i, cmd);
		else if (line[i] == '$')
			i = ft_dollar(line, i, cmd);
		else if ((line[i] == '<' || line[i] == '>')
			&& ft_get_state(line, i) == base)
			i = ft_redir(line, i, cmd);
		else if (line[i] == '|')
			i = ft_pipe(line, i, cmd);
		else
			i++;
	}
	cmd->token[cmd->p] = 0;
	ft_redir_type(cmd);
}

int	ft_check_quest(char *line)
{
	int	i;

	if (line[0] == '?')
		return (0);
	i = 0;
	while (line[++i])
	{
		if (line[i] == '?' && line[i - 1] != '$'
			&& ft_get_state(line, i) == base)
			return (0);
	}
	return (1);
}
