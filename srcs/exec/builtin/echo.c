/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:20:33 by amonier           #+#    #+#             */
/*   Updated: 2023/09/16 22:01:57 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_flag(t_cmd *act_cmd, int pos_in_cmd)
{
	int	i;

	i = 0;
	if (act_cmd->cmd[pos_in_cmd][i] == '\0')
		return (0);
	while ((act_cmd->cmd)[pos_in_cmd][i])
	{
		if (i == 0)
		{
			if ((act_cmd->cmd)[pos_in_cmd][i] != '-')
				return (0);
		}
		else
		{
			if ((act_cmd->cmd)[pos_in_cmd][i] != 'n')
				return (0);
		}
		i++;
	}
	return (1);
}

int	*tab_of_flag(t_cmd *act_cmd, t_mini *minsh, int size)
{
	int	*flag_tab;
	int	i;

	i = 0;
	flag_tab = malloc(sizeof(int) * size);
	if (flag_tab == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	while ((act_cmd->cmd)[i])
	{
		if (i == 0)
			flag_tab[i] = 2;
		else
		{
			flag_tab[i] = is_a_flag(act_cmd, i);
		}
		i++;
	}
	return (flag_tab);
}

int	begin_the_print_from_here(t_cmd *act_cmd, t_mini *minsh, int size)
{
	int	*flag_tab;
	int	i;

	flag_tab = tab_of_flag(act_cmd, minsh, size);
	i = 1;
	while (i < size)
	{
		if (flag_tab[i] == 0)
		{
			free(flag_tab);
			return (i);
		}
		i++;
	}
	free(flag_tab);
	return (-1);
}

void	print_cmd(t_mini *minsh, int position, int i, int flag)
{
	int	size;

	size = size_double_tab((minsh->cmds)[position].cmd);
	while (((minsh->cmds)[position].cmd)[i])
	{
		if (i == size - 1)
		{
			if (flag == 0)
				secure_printf(minsh, position, \
				((minsh->cmds)[position].cmd)[i], 1);
			else
				secure_printf(minsh, position, \
				((minsh->cmds)[position].cmd)[i], 0);
		}
		else
		{
			secure_printf(minsh, position, ((minsh->cmds)[position].cmd)[i], 0);
			secure_printf(minsh, position, " ", 0);
		}
		i++;
	}
}

void	b_echo(t_mini *minsh, int position)
{
	int	size;
	int	i;
	int	flag;

	size = size_double_tab((minsh->cmds)[position].cmd);
	if (size >= 2)
	{
		i = begin_the_print_from_here(&((minsh->cmds)[position]), minsh, size);
		if (i == -1)
		{
			free_t_mini(minsh);
			exit(0);
		}
		else
		{
			flag = (i > 1);
			print_cmd(minsh, position, i, flag);
		}
	}
	else
		secure_printf(minsh, position, "\n", 0);
	free_t_mini(minsh);
	exit(0);
}
