/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_double_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 04:46:55 by alex              #+#    #+#             */
/*   Updated: 2023/08/09 18:18:53 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_double_tab(char **tab_char)
{
	int	i;

	i = 0;
	if (tab_char == NULL || *tab_char == NULL)
		return (i);
	while (tab_char[i])
		i++;
	return (i);
}
