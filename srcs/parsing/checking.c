/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:47:14 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/29 18:46:19 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_correct_char(char c)
{
	return (c == ';' || c == '&' || c == '(' || c == ')' || c == '`'
		|| c == '\\');
}

char	ft_check_dt(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_get_state(str, i) == base && ft_correct_char(str[i]))
			return (str[i]);
	}
	return (0);
}

int	ft_check_pipes(char *str)
{
	int	i;
	int	state;
	int	before;

	i = -1;
	state = 0;
	before = 0;
	while (str[++i])
	{
		if (ft_get_state(str, i) == base && str[i] == '|')
		{
			if (!state && before)
				state = 1;
			else
				return (0);
		}
		else if (ft_get_state(str, i) == base && str[i] != '|'
			&& str[i] != ' ' && str[i] != '\t')
		{
			state = 0;
			before = 1;
		}
	}
	return (!state);
}

int	ft_wf(char **input, char **output, int *redir_type)
{
	int	i;
	int	k;
	int	l;

	i = -1;
	k = 0;
	l = 0;
	while (redir_type[++i])
	{
		if (redir_type[i] == redir_double_right)
			if (!ft_strlen(output[l++]))
				return (4);
		if (redir_type[i] == redir_double_left)
			if (!ft_strlen(input[k++]))
				return (2);
		if (redir_type[i] == redir_left)
			if (!ft_strlen(input[k++]))
				return (1);
		if (redir_type[i] == redir_right)
			if (!ft_strlen(output[l++]))
				return (3);
	}
	return (0);
}

char	ft_check_triple_redir(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i + 2 <= (int)ft_strlen(str))
		{
			if (ft_get_state(str, i) == base
				&& ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
					|| (str[i] == '>' && str[i + 1] == '>'
						&& str[i + 2] == '>')))
				return (str[i]);
		}
	}
	return (0);
}
