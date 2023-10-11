/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonier <amonier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:08:45 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/06 18:54:08 by amonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envstrcmp(char *str, char *tosearch)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != tosearch[i])
			return (0);
		i++;
	}
	if (str[i] == '=' && tosearch[i] == '\0')
		return (1);
	return (0);
}

int	ft_env_size(char **envp)
{
	int	res;

	res = 0;
	if (envp == NULL || *envp == NULL)
		return (res);
	while (envp[res])
		res++;
	return (res);
}

char	*ft_get_var(char **env, char *var)
{
	int	i;

	i = -1;
	while (++i < ft_env_size(env))
	{
		if (ft_envstrcmp(env[i], var))
			break ;
	}
	if (i == ft_env_size(env))
		return (NULL);
	else
		return (env[i] + ft_strlen(var) + 1);
}

char	**ft_realloc_env(char **envp)
{
	char	**res;
	int		i;

	res = ft_calloc(sizeof(char *), (ft_env_size(envp) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!(res[i]))
		{
			while (i + 1)
				free(res[i--]);
			free(res);
			return (NULL);
		}
	}
	return (res);
}

void	ft_clean_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env[i]);
	free(env);
	return ;
}
