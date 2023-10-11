/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:09:23 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/04 15:32:02 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	good_path(t_mini *minsh, t_cmd *macmd, int pos)
{
	char	*temp_cmd;
	char	*err;

	temp_cmd = malloc((ft_strlen((macmd->cmd)[0]) - pos) * sizeof(char));
	if (temp_cmd == NULL)
	{
		free_t_mini(minsh);
		exit(errno);
	}
	copy_cmd(temp_cmd, &pos, macmd);
	(macmd->path) = ft_strdup((macmd->cmd)[0]);
	free((macmd->cmd)[0]);
	(macmd->cmd)[0] = ft_strdup(temp_cmd);
	free(temp_cmd);
	if (execve((macmd->path), (macmd->cmd), minsh->envp))
	{
		err = ft_strjoin_triple((macmd->cmd)[0], ": ", strerror(errno));
		print_error(err);
		free(err);
		free_t_mini(minsh);
		exit(errno);
	}
	free_t_mini(minsh);
	exit(errno);
}

void	cmd_no_path(t_cmd *macmd, t_mini *minsh)
{
	int		pos;

	pos = find_last_char((macmd->cmd)[0], '/');
	if (pos == -1)
		err_cmd_not_found(minsh, macmd);
	else
	{
		if (access((macmd->cmd)[0], F_OK & X_OK) == -1)
			err_file_not_found(minsh, macmd, errno);
		else
			good_path(minsh, macmd, pos);
	}
}

void	not_numeric_arg(t_mini *minsh, int position)
{
	char	*str;

	str = ft_strjoin_triple("exit : ", (minsh->cmds[position]).cmd[1], \
		": numeric argument required\n");
	print_error(str);
	free(str);
	free_t_mini(minsh);
	exit(2);
}

void	exit_in_child(t_mini *minsh, int position)
{
	int	err;

	if (size_double_tab((minsh->cmds[position]).cmd) >= 2)
		if (check_number((minsh->cmds[position]).cmd[1]) == 0)
			not_numeric_arg(minsh, position);
	if (size_double_tab((minsh->cmds[position]).cmd) > 2)
	{
		ft_putstr_fd("exit: Too many arguments\n", 2);
		free_t_mini(minsh);
		exit(1);
	}
	if (size_double_tab((minsh->cmds[position]).cmd) == 1)
	{
		free_t_mini(minsh);
		exit(0);
	}
	else
	{
		err = ft_atoi((minsh->cmds[position]).cmd[1]);
		free_t_mini(minsh);
		exit(err);
	}
}
