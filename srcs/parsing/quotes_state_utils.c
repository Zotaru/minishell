/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_state_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:35:40 by jehubert          #+#    #+#             */
/*   Updated: 2023/07/03 11:21:53 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_process_base(char c, t_state state)
{
	if (c == '\'')
		return (s_quote);
	else if (c == '\"')
		return (d_quote);
	else
		return (state);
}

t_state	ft_process_single_quote(char c, t_state state)
{
	if (c == '\'')
		return (base);
	else if (c == '\"')
		return (double_in_single);
	else
		return (state);
}

t_state	ft_process_double_quote(char c, t_state state)
{
	if (c == '\"')
		return (base);
	else if (c == '\'')
		return (single_in_double);
	else
		return (state);
}

t_state	ft_process_single_in_double(char c, t_state state)
{
	if (c == '\'')
		return (d_quote);
	else if (c == '\"')
		return (base);
	else
		return (state);
}

t_state	ft_process_double_in_single(char c, t_state state)
{
	if (c == '\"')
		return (s_quote);
	else if (c == '\'')
		return (base);
	else
		return (state);
}
