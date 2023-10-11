/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_four.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:50:36 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 22:09:17 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	equal_in_string(t_mini *minsh, int pos, int equal_pos, int i)
{
	int	valid;

	if (equal_pos == 1 && ((minsh->cmds)[pos].cmd[i])[equal_pos - 1] == '+')
		valid = -1;
	else if (((minsh->cmds)[pos].cmd[i])[equal_pos - 1] == '+')
		valid = is_valid_variable((minsh->cmds)[pos].cmd[i], equal_pos - 1);
	else
		valid = is_valid_variable((minsh->cmds)[pos].cmd[i], equal_pos);
	if (valid == -1)
	{
		ft_putstr_fd((minsh->cmds)[pos].cmd[i], 2);
		ft_putstr_fd(" is not de valid identifier\n", 2);
		return (1);
	}
	else if (((minsh->cmds)[pos].cmd[i])[equal_pos - 1] != '+')
		upd_env(minsh, pos, i, equal_pos);
	else if (((minsh->cmds)[pos].cmd[i])[equal_pos - 1] == '+')
		upd_env_plus(minsh, pos, i, equal_pos);
	return (0);
}

int	print_not_valid_identifier(t_mini *minsh, int pos, int i)
{
	ft_putstr_fd((minsh->cmds)[pos].cmd[i], 2);
	ft_putstr_fd(" is not de valid identifier\n", 2);
	return (1);
}

int	b_export(t_mini *minsh, int pos)
{
	int	i;
	int	equal_pos;
	int	err;

	err = 0;
	if (size_double_tab((minsh->cmds)[pos].cmd) == 1)
	{
		print_alpha_env(minsh, pos, minsh->envp);
		return (err);
	}
	i = 1;
	while ((minsh->cmds)[pos].cmd[i])
	{
		equal_pos = find_char((minsh->cmds)[pos].cmd[i], '=');
		if (equal_pos == 0)
			err = print_not_valid_identifier(minsh, pos, i);
		else if (equal_pos > 0)
			err = equal_in_string(minsh, pos, equal_pos, i);
		else if (equal_pos == -1)
			err = export_no_equal(minsh, pos, i);
		i++;
	}
	return (err);
}
