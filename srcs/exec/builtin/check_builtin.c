/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 03:34:39 by alex              #+#    #+#             */
/*   Updated: 2023/08/05 03:08:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (echo_enum);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (cd_enum);
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (pwd_enum);
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (export_enum);
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (unset_enum);
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (env_enum);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (exit_enum);
	return (not_builtin);
}
