/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:30:33 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/05 15:51:25 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_var_name_bis(char *arg, int i, int *k, char **env)
{
	int		j;
	char	*var;
	char	*res;

	if (!env)
		return (NULL);
	j = i;
	var = NULL;
	while (ft_isalnum(arg[j]) || arg[j] == '_')
		j++;
	var = ft_substr(arg, i, j - i);
	res = ft_strdup(ft_get_var(env, var));
	free(var);
	*k = j - i;
	return (res);
}

static char	*ft_quest_bis(int *k)
{
	extern int	g_status;
	char		*var;

	var = ft_itoa(g_status);
	*k = 1;
	return (var);
}

static char	*ft_dol_replace_bis(char *arg, int i, char **env)
{
	int		name_len;
	char	*var;
	char	*tmp;
	char	*tpm;
	char	*new_arg;

	if (arg[i + 1] == '?')
		var = ft_quest_bis(&name_len);
	else
		var = ft_var_name_bis(arg, i + 1, &name_len, env);
	if (!var)
		var = ft_strdup("");
	tmp = ft_substr(arg, 0, i);
	new_arg = ft_strjoin(tmp, var);
	free(tmp);
	free(var);
	tmp = ft_substr(arg, i + name_len + 1, ft_strlen(arg) - 1);
	tpm = ft_strjoin(new_arg, tmp);
	free(new_arg);
	new_arg = tpm;
	free(tmp);
	free(arg);
	return (new_arg);
}

char	*ft_dol_search_bis(char *arg, char **env)
{
	static int	i = -1;

	while (++i < (int)ft_strlen(arg))
	{
		if (arg[i] == '$' && (ft_isalnum(arg[i + 1]) || arg[i + 1] == '?'
				|| arg[i + 1] == '_'))
		{
			if (ft_get_state(arg, i) == base
				|| ft_get_state(arg, i) == d_quote
				|| ft_get_state(arg, i) == single_in_double)
				break ;
		}
	}
	if (i < (int)ft_strlen(arg))
	{
		arg = ft_dol_replace_bis(arg, i, env);
		return (ft_dol_search_bis(arg, env));
	}
	else
	{
		i = -1;
		return (arg);
	}
}
