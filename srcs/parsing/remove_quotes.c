/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:48:48 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/20 20:04:46 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wo_quote_len(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (i)
			{
				if (((ft_get_state(str, i - 1) == base
							&& ft_get_state(str, i) != base)
						|| (ft_get_state(str, i - 1) != base
							&& ft_get_state(str, i) == base)))
					res--;
			}
			else
			res--;
		}
	}
	return (res);
}

static void	ft_fill_quotes(char *str, char *dst)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (i)
		{
			if (!((ft_get_state(str, i - 1) == base
						&& ft_get_state(str, i) != base)
					|| (ft_get_state(str, i - 1) != base
						&& ft_get_state(str, i) == base)))
				dst[j++] = str[i];
		}
		else
			if (str[i] != '\'' && str[i] != '\"')
				dst[j++] = str[i];
	}
}

char	*ft_wo_quote(char *str)
{
	char	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(char), ft_wo_quote_len(str) + 1);
	if (!new)
		return (NULL);
	ft_fill_quotes(str, new);
	return (free(str), new);
}

void	ft_replace_quotes(t_cmd *cmd, int len)
{
	int	i;

	i = -1;
	while (++i < cmd->redir_in)
		cmd->input_file[i] = ft_wo_quote(cmd->input_file[i]);
	i = -1;
	while (++i < cmd->redir_out)
		cmd->output_file[i] = ft_wo_quote(cmd->output_file[i]);
	if (!cmd->cmd)
		return ;
	i = -1;
	while (++i < len)
		cmd->cmd[i] = ft_wo_quote(cmd->cmd[i]);
}
