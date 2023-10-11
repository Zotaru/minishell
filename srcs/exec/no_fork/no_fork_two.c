/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_fork_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:28:18 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/09 17:29:07 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_fork(t_mini *minsh)
{
	int			enum_cmd;
	int			err_files;
	extern int	g_status;

	err_files = files(minsh, NULL, 0, 0);
	if (err_files == 1)
		return ;
	if ((minsh->cmds)[0].cmd == NULL)
		return ;
	enum_cmd = check_builtin((minsh->cmds)[0].cmd);
	if (enum_cmd == cd_enum)
		g_status = b_cd(minsh, 0);
	else if (enum_cmd == export_enum)
		g_status = b_export(minsh, 0);
	else if (enum_cmd == unset_enum)
		g_status = b_unset(minsh, 0);
	else if (enum_cmd == exit_enum)
		exit_not_in_fork(minsh);
	return ;
}
