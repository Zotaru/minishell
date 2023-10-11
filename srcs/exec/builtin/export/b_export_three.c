/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:47:12 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/11 04:16:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*supp_plus(char *str, int pos_equal)
{
	char	*new_str;
	char	*begin;
	char	*end;
	int		len;

	len = ft_strlen(str);
	begin = malloc(sizeof(char) * (pos_equal - 1 + 1));
	if (begin == NULL)
		return (NULL);
	end = malloc(sizeof(char) * (len - pos_equal + 1));
	if (end == NULL)
		return (secur_alloc_supp_plus(begin));
	normi_supp_plus_2(str, begin, end, pos_equal);
	new_str = normi_supp_plus(begin, end, pos_equal, len);
	return (new_str);
}

char	**create_new_env_with_plus(t_mini *minsh, int s_env, int *i)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (s_env + 1 + 1));
	if (new_env == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	while (*i < s_env)
	{
		new_env[*i] = ft_strdup((minsh->envp)[*i]);
		if (new_env[*i] == NULL)
			security_malloc_for_new_env(minsh, new_env, *i);
		(*i)++;
	}
	return (new_env);
}

void	normi_maj_envp(t_mini *minsh, char **new_env, int *i)
{
	(*i)++;
	new_env[*i] = NULL;
	free_double_tab_char(minsh->envp);
	minsh->envp = new_env;
}

int	var_in_env_with_plus(t_mini *minsh, int pos, int p_arg, int pos_equal)
{
	int	i;
	int	s_env;

	i = 0;
	s_env = size_double_tab(minsh->envp);
	if ((minsh->envp) != NULL && *(minsh->envp) != NULL)
	{
		while ((minsh->envp)[i])
		{
			if (ft_strncmp((minsh->envp)[i], (minsh->cmds)[pos].cmd[p_arg] \
			, pos_equal - 1) == 0)
			{
				(minsh->envp)[i] = join_for_plus((minsh->envp)[i], \
				(minsh->cmds)[pos].cmd[p_arg], pos_equal);
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

void	upd_env_plus(t_mini *minsh, int pos, int p_arg, int pos_equal)
{
	int		s_env;
	int		i;
	char	**new_env;

	s_env = size_double_tab(minsh->envp);
	if (var_in_env_with_plus(minsh, pos, p_arg, pos_equal) == 1)
		return ;
	i = 0;
	new_env = create_new_env_with_plus(minsh, s_env, &i);
	new_env[i] = supp_plus((minsh->cmds)[pos].cmd[p_arg], pos_equal);
	if (new_env[i] == NULL)
		security_malloc_for_new_env(minsh, new_env, i);
	normi_maj_envp(minsh, new_env, &i);
}
