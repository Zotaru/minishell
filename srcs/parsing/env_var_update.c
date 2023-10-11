/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:15:21 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/28 16:59:00 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_pwd(char **env, char *oldpwd, char *pwd)
{
	int		i;
	char	*newpwd;
	char	*newoldpwd;

	i = -1;
	newpwd = ft_strdup(pwd);
	if (!newpwd)
		return (1);
	newoldpwd = ft_strdup(oldpwd);
	if (!newoldpwd)
		return (free(newpwd), 1);
	while (++i < ft_env_size(env))
	{
		if (!ft_strncmp("PWD", env[i], ft_strlen("PWD")))
		{
			free(env[i]);
			env[i] = newpwd;
		}
		if (!ft_strncmp("OLDPWD", env[i], ft_strlen("OLDPWD")))
		{
			free(env[i]);
			env[i] = newoldpwd;
		}
	}
	return (0);
}

static int	ft_new_var(char **env, char *var)
{
	char	**newenv;
	int		i;

	i = -1;
	newenv = ft_calloc(sizeof(char *), (ft_env_size(env) + 2));
	if (!newenv)
		return (1);
	while (++i < ft_env_size(env) + 1)
	{
		if (i != ft_env_size(env))
			newenv[i] = ft_strdup(env[i]);
		else
			newenv[i] = ft_strdup(var);
		if (!newenv[i])
		{
			while (i + 1)
				free(newenv[i--]);
			free(newenv);
			return (1);
		}
	}
	free(env);
	free(var);
	env = newenv;
	return (0);
}

int	ft_add_var(char **env, char *var, char *name)
{
	int		i;
	char	*tmp;
	char	*newvar;

	i = -1;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (1);
	newvar = ft_strjoin(tmp, name);
	if (!newvar)
		return (free(tmp), 1);
	free(tmp);
	while (++i < ft_env_size(env))
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
		{
			free(env[i]);
			env[i] = newvar;
			return (0);
		}
	}
	return (ft_new_var(env, newvar));
}
