/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_double_tab_int.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:28:05 by amonier           #+#    #+#             */
/*   Updated: 2023/06/09 03:43:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_double_tab_int(int **fd_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(fd_tab[i]);
		i++;
	}
	free(fd_tab);
}
