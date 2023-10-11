/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:41:36 by amonier           #+#    #+#             */
/*   Updated: 2023/08/09 18:10:58 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_both(t_mini *minsh, char *s_new, char *s_old)
{
	int	i;

	i = 0;
	while (ft_strncmp((minsh->envp)[i], "PWD=", 4) != 0)
		i++;
	free((minsh->envp)[i]);
	(minsh->envp)[i] = ft_strjoin("PWD=", s_new);
	if ((minsh->envp)[i] == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	i = 0;
	while (ft_strncmp((minsh->envp)[i], "OLDPWD=", \
	(int)ft_strlen("OLDPWD=")) != 0)
		i++;
	free((minsh->envp)[i]);
	(minsh->envp)[i] = ft_strjoin("OLDPWD=", s_old);
	if ((minsh->envp)[i] == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
}

int	change_dir(t_mini *minsh, int position, int size)
{
	if (size == 1)
	{
		if (chdir("/home"))
		{
			perror("chdir fail\n");
			return (1);
		}
	}
	else
	{
		if (chdir(((minsh->cmds)[position]).cmd[1]))
		{
			perror(((minsh->cmds)[position]).cmd[1]);
			return (1);
		}
	}
	return (0);
}

int	check_in_env(char *str, int len, t_mini *minsh)
{
	int	i;

	if ((minsh->envp) == NULL || *(minsh->envp) == NULL)
		return (-1);
	i = 0;
	while ((minsh->envp)[i])
	{
		if (ft_strncmp((minsh->envp)[i], str, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	check_for_create_env(t_mini *minsh)
{
	int	pwd;
	int	oldpwd;

	pwd = check_in_env("PWD=", 4, minsh);
	oldpwd = check_in_env("OLDPWD=", 7, minsh);
	if (pwd == -1 && oldpwd == -1)
		return (-1);
	else if (pwd >= 0 && oldpwd >= 0)
		return (2);
	else if (pwd >= 0 && oldpwd == -1)
		return (0);
	else if (pwd == -1 && oldpwd >= 0)
		return (1);
	return (-1);
}

void	ft_free_one(char *sfree, char *sjoin, t_mini *minsh)
{
	free(sfree);
	free(sjoin);
	free_t_mini(minsh);
	exit(1);
}
