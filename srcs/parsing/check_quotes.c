/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:28:47 by jehubert          #+#    #+#             */
/*   Updated: 2023/07/01 16:42:54 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote_syntax(char *str)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !in_double)
		{
			if (in_single == 0)
				in_single = 1;
			else
				in_single = 0;
		}
		else if (str[i] == '\"' && !in_single)
		{
			if (in_double == 0)
				in_double = 1;
			else
				in_double = 0;
		}
	}
	return (!in_single && !in_double);
}
