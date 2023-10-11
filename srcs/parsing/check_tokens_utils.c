/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 01:18:49 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/11 23:04:51 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir(char *line, int i, t_cmd *cmd)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		cmd->token[cmd->p++] = REDIR_DOUBLE_LEFT;
		i = i + 2;
	}
	else if (line [i] == '<')
	{
		cmd->token[cmd->p++] = REDIR_LEFT;
		i++;
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		cmd->token[cmd->p++] = REDIR_DOUBLE_RIGHT;
		i = i + 2;
	}
	else if (line[i + 1] != '>')
	{
		cmd->token[cmd->p++] = REDIR_RIGHT;
		i++;
	}
	cmd->redir++;
	return (i);
}

int	ft_dollar(char *line, int i, t_cmd *cmd)
{
	if (line[i++] == '$' && line[i] == '?')
		cmd->token[cmd->p++] = DOLLAR_QUESTION;
	else
	{
		cmd->token[cmd->p++] = DOLLAR;
		while (line[i] && ft_isalnum(line[i]))
			i++;
	}
	return (i);
}

int	ft_pipe(char *line, int i, t_cmd *cmd)
{
	if (line[i] == '|')
		i++;
	cmd->token[cmd->p++] = PIPE_TOKEN;
	return (i);
}

int	ft_quote(char *line, int i, t_cmd *cmd)
{
	char	quote;
	char	*quote_type;

	quote = line[i];
	if (quote == '"')
		quote_type = DOUBLE_QUOTE;
	else
		quote_type = SIMPLE_QUOTE;
	i++;
	cmd->token[cmd->p++] = quote_type;
	return (i);
}
