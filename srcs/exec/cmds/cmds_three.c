/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:12:45 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/09 17:13:26 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_export_unset(t_mini *minsh, int position, int enum_val)
{
	int	err;

	if (enum_val == cd_enum)
	{
		err = b_cd(minsh, position);
		free_t_mini(minsh);
		exit(err);
	}
	else if (enum_val == export_enum)
	{
		err = b_export(minsh, position);
		free_t_mini(minsh);
		exit(err);
	}
	else if (enum_val == unset_enum)
	{
		err = b_unset(minsh, position);
		free_t_mini(minsh);
		exit(err);
	}
	return ;
}

void	cmds(t_mini *minsh, int position)
{
	int	enum_val;

	enum_val = check_builtin(((minsh->cmds)[position].cmd));
	cd_export_unset(minsh, position, enum_val);
	if (enum_val == echo_enum)
		b_echo(minsh, position);
	else if (enum_val == pwd_enum)
		pwd(minsh, position);
	else if (enum_val == env_enum)
		b_env(minsh, position);
	else if (enum_val == exit_enum)
		exit_in_child(minsh, position);
	else if (enum_val == not_builtin)
	{
		if (((minsh->cmds)[position]).path == NULL)
			cmd_no_path(&((minsh->cmds)[position]), minsh);
		else
			cmd_with_path(&((minsh->cmds)[position]), minsh);
	}
	exit(0);
}
