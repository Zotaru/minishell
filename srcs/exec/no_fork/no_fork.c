/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:50:26 by amonier           #+#    #+#             */
/*   Updated: 2023/09/16 21:55:10 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_number(char *str)
{
	unsigned long long	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > 19)
		return (0);
	i = ft_atoi_long_long(str);
	if (i > LONG_MAX)
		return (0);
	return (1);
}

void	numeric_arg_required(t_mini *minsh)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd((minsh->cmds[0]).cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_t_mini(minsh);
	rl_clear_history();
	exit(2);
}

void	classic_exit(t_mini *minsh)
{
	free_t_mini(minsh);
	rl_clear_history();
	exit(0);
}

void	exit_with_int(t_mini *minsh)
{
	extern int	g_status;

	g_status = ft_atoi((minsh->cmds[0]).cmd[1]);
	free_t_mini(minsh);
	rl_clear_history();
	exit(g_status);
}

void	exit_not_in_fork(t_mini *minsh)
{
	extern int	g_status;

	ft_putstr_fd("exit\n", 2);
	if (size_double_tab((minsh->cmds[0]).cmd) >= 2)
	{
		if (check_number((minsh->cmds[0]).cmd[1]) == 0)
			numeric_arg_required(minsh);
	}
	if (size_double_tab((minsh->cmds[0]).cmd) > 2)
	{
		ft_putstr_fd("exit : Too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	if (size_double_tab((minsh->cmds[0]).cmd) == 1)
		classic_exit(minsh);
	else
		exit_with_int(minsh);
}
