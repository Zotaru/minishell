/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:17:02 by alex              #+#    #+#             */
/*   Updated: 2023/08/09 18:02:44 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	security_malloc(t_mini *minsh, char **new_env)
{
	free_double_tab_char(new_env);
	free_t_mini(minsh);
	exit(1);
}

int	is_in_env(t_mini *minsh, int position, int position_cmd)
{
	int	i;

	i = 0;
	while ((minsh->envp)[i])
	{
		if (ft_strncmp((minsh->envp)[i], \
		(minsh->cmds)[position].cmd[position_cmd], \
		ft_strlen((minsh->cmds)[position].cmd[position_cmd])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**create_new_env(t_mini *minsh, int size_env, int env_pos)
{
	char	**new_env;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_env = malloc((size_env - 1 + 1) * sizeof(char *));
	if (new_env == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	while ((minsh->envp)[i])
	{
		if (i != env_pos)
		{
			new_env[j] = ft_strdup((minsh->envp)[i]);
			if (new_env[j] == NULL)
				security_malloc(minsh, new_env);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	delete_in_env(t_mini *minsh, int env_pos)
{
	char	**new_env;
	int		size_env;

	size_env = size_double_tab(minsh->envp);
	new_env = create_new_env(minsh, size_env, env_pos);
	free_double_tab_char(minsh->envp);
	minsh->envp = new_env;
}

int	b_unset(t_mini *minsh, int position)
{
	int	size;
	int	i;
	int	env_pos;

	size = size_double_tab((minsh->cmds)[position].cmd);
	if (size == 1 || minsh->envp == NULL || *(minsh->envp) == NULL)
		return (0);
	i = 1;
	while ((minsh->cmds)[position].cmd[i])
	{
		env_pos = is_in_env(minsh, position, i);
		if (env_pos != -1)
			delete_in_env(minsh, env_pos);
		i++;
	}
	return (0);
}
