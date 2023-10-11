/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:00:23 by alex              #+#    #+#             */
/*   Updated: 2023/09/11 03:37:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_mini *minsh, int position)
{
	int	size;
	int	i;

	if ((minsh->envp) == NULL || *(minsh->envp) == NULL)
		exit(0);
	size = size_double_tab((minsh->cmds)[position].cmd);
	if (size > 1)
	{
		print_error("env : too many arguments\n");
		free_t_mini(minsh);
		exit(1);
	}
	i = 0;
	while ((minsh->envp)[i])
	{
		if (find_char((minsh->envp)[i], '=') != -1)
			secure_printf(minsh, position, (minsh->envp)[i], 1);
		i++;
	}
	free_t_mini(minsh);
	exit(0);
}
