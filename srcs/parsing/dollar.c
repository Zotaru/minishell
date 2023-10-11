/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:50:34 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/29 19:00:41 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_var_name(char *arg, int i, int *k, char **env)
{
	char	*var;
	char	*res;

	var = ft_substr(arg, i, *k);
	res = ft_strdup(ft_get_var(env, var));
	free(var);
	return (res);
}

static char	*ft_quest(int *k)
{
	extern int	g_status;
	char		*var;

	var = ft_itoa(g_status);
	*k = 1;
	return (var);
}

static char	*ft_dol_replace(char *arg, int i, char **env, int *name_len)
{
	char	*var;
	char	*tmp;
	char	*tpm;
	char	*new_arg;

	if (arg[i + 1] == '?')
		var = ft_quest(name_len);
	else
		var = ft_var_name(arg, i + 1, name_len, env);
	if (!var)
		return (free(arg), ft_strdup(""));
	tmp = ft_substr(arg, 0, i);
	new_arg = ft_strjoin(tmp, var);
	free(tmp);
	free(var);
	tmp = ft_substr(arg, i + *name_len + 1, ft_strlen(arg) - 1);
	tpm = ft_strjoin(new_arg, tmp);
	free(new_arg);
	new_arg = tpm;
	free(tmp);
	free(arg);
	return (new_arg);
}

char	*ft_dol_search(char *arg, char **env, t_cmd *cmd, int *j)
{
	static int	i = -1;
	int			tmp;

	while (++i < (int)ft_strlen(arg))
	{
		if (ft_strchr("$", arg[i]))
			if (cmd->to_expand[(*j)++])
				break ;
	}
	if (i < (int)ft_strlen(arg))
	{
		tmp = (int)ft_strlen(arg);
		arg = ft_dol_replace(arg, i, env, &((cmd->var_len)[*j - 1]));
		if (tmp > (int)ft_strlen(arg))
			i--;
		return (ft_dol_search(arg, env, cmd, j));
	}
	else
	{
		i = -1;
		return (arg);
	}
}
