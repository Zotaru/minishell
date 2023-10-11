/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 03:42:19 by alex              #+#    #+#             */
/*   Updated: 2023/08/21 11:52:00 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_with_path(t_cmd *macmd, t_mini *minsh)
{
	char	*final_path;
	char	*err;

	final_path = ft_strjoin(macmd->path, (macmd->cmd)[0]);
	if (execve(final_path, macmd->cmd, minsh->envp))
	{
		err = ft_strjoin_triple((macmd->cmd)[0], ": ", strerror(errno));
		err = ft_tjoin(err, "\n");
		print_error(err);
		free(err);
		free_t_mini(minsh);
		free(final_path);
		exit(errno);
	}
	if (final_path != NULL)
		free(final_path);
	free_t_mini(minsh);
	exit(0);
}

int	find_last_char(char	*str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	err_cmd_not_found(t_mini *minsh, t_cmd *macmd)
{
	char	*err_str;

	err_str = ft_strjoin((macmd->cmd)[0], " : command not found\n");
	if (err_str == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	print_error(err_str);
	free(err_str);
	free_t_mini(minsh);
	exit(127);
}

void	err_file_not_found(t_mini *minsh, t_cmd *macmd, int err)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin_triple((macmd->cmd)[0], " : ", strerror(err));
	if (temp == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	str = ft_strjoin(temp, "\n");
	if (str == NULL)
	{
		free(temp);
		free_t_mini(minsh);
		exit(1);
	}
	print_error(str);
	free(str);
	free(temp);
	free_t_mini(minsh);
	exit(126);
}

void	copy_cmd(char *temp_cmd, int *pos, t_cmd *macmd)
{
	int	i;

	i = 0;
	(*pos)++;
	while ((*pos) < (int)ft_strlen((macmd->cmd)[0]))
	{
		temp_cmd[i] = ((macmd->cmd)[0])[(*pos)];
		i++;
		(*pos)++;
	}
	temp_cmd[i] = '\0';
	return ;
}
