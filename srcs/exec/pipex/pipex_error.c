/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:20:28 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/09 17:23:01 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_error(int **pfd, t_mini *minsh)
{
	print_error("Error: pipe failed\n");
	if (pfd[1][0] > 0)
		close(pfd[1][0]);
	clear_double_tab_int(pfd, 2);
	free_t_mini(minsh);
	exit(1);
}
