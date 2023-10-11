/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:09:44 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 22:11:14 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_char(char *str, char c)
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

int	is_valid_variable(char *str, int equal_position)
{
	int	i;

	i = 0;
	while (i < equal_position)
	{
		if (i == 0)
		{
			if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A'
					&& str[i] <= 'Z') && !(str[i] == '_'))
				return (-1);
		}
		else
		{
			if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A'
					&& str[i] <= 'Z') && !(str[i] == '_')
				&& !(str[i] >= '1' && str[i] <= '9'))
				return (-1);
		}
		i++;
	}
	return (0);
}

void	security_malloc_for_new_env(t_mini *minsh, char **new_env, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(new_env[j]);
		j++;
	}
	free(new_env);
	free_t_mini(minsh);
	exit(1);
}

char	**create_new_env_no_plus(t_mini *minsh, int s_env, int pos, int p_arg)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (s_env + 1 + 1));
	if (new_env == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	while (i < s_env)
	{
		new_env[i] = ft_strdup((minsh->envp)[i]);
		if (new_env[i] == NULL)
			security_malloc_for_new_env(minsh, new_env, i);
		i++;
	}
	new_env[i] = ft_strdup((minsh->cmds)[pos].cmd[p_arg]);
	if (new_env[i] == NULL)
		security_malloc_for_new_env(minsh, new_env, i);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

int	var_in_env_no_plus(t_mini *minsh, int pos, int p_arg, int pos_equal)
{
	int	i;
	int	s_env;

	i = 0;
	s_env = size_double_tab(minsh->envp);
	if ((minsh->envp) != NULL && *(minsh->envp) != NULL)
	{
		while ((minsh->envp)[i])
		{
			if (ft_strncmp((minsh->envp)[i], (minsh->cmds)[pos].cmd[p_arg], \
			pos_equal) == 0)
			{
				free((minsh->envp)[i]);
				(minsh->envp)[i] = ft_strdup((minsh->cmds)[pos].cmd[p_arg]);
				if ((minsh->envp)[i] == NULL)
				{
					free_t_mini_export(minsh, s_env);
					exit(1);
				}
				return (1);
			}
			i++;
		}
	}
	return (0);
}
