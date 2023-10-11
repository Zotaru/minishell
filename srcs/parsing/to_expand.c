/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:43:40 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 20:03:17 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_len_name(int i, char *arg)
{
	int	len;

	len = 0;
	i++;
	if (arg[i] == '\'' || arg[i] == '\"')
		return (0);
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
	{
		len++;
		i++;
	}
	if (len == -1)
		len = 0;
	return (len);
}

int	ft_is_expandable(char *arg, int i)
{
	if (arg[i] == '$' && (ft_isalnum(arg[i + 1]) || arg[i + 1] == '?'
			|| arg[i + 1] == '_' || arg[i + 1] == '\"' || arg[i + 1] == '\''))
	{
		if (ft_get_state(arg, i) == base
			|| ft_get_state(arg, i) == d_quote
			|| ft_get_state(arg, i) == single_in_double)
			return (1);
	}
	return (0);
}

static void	ft_alloc_expand(char *arg, t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!arg)
	{
		cmd->to_expand = ft_calloc(1, 1);
		cmd->var_len = ft_calloc(1, 1);
		return ;
	}
	while (arg[++i])
	{
		if (ft_strchr("$", arg[i]))
			j++;
	}
	cmd->to_expand = ft_calloc(sizeof(int), j);
	cmd->var_len = ft_calloc(sizeof(int), j);
}

void	ft_to_expand(char *arg, t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	ft_alloc_expand(arg, cmd);
	if (!arg)
		return ;
	while (arg[++i])
	{
		if (ft_strchr("$", arg[i]))
		{
			if (ft_is_expandable(arg, i))
			{
				cmd->to_expand[j] = 1;
				cmd->var_len[j] = ft_get_len_name(i, arg);
			}
			j++;
		}
	}
}
