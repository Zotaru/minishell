/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:44:58 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 22:10:26 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	upd_env(t_mini *minsh, int pos, int p_arg, int pos_equal)
{
	int		s_env;
	char	**new_env;

	s_env = size_double_tab(minsh->envp);
	if (var_in_env_no_plus(minsh, pos, p_arg, pos_equal) == 1)
		return (0);
	new_env = create_new_env_no_plus(minsh, s_env, pos, p_arg);
	free_double_tab_char(minsh->envp);
	minsh->envp = new_env;
	return (0);
}

char	*join_for_plus(char *envp_to_change, char *str_to_join, int pos_equal)
{
	char	*new_str;

	if (find_char(envp_to_change, '=') >= 0)
		new_str = ft_strjoin(envp_to_change, &(str_to_join[pos_equal + 1]));
	else
		new_str = ft_strjoin_triple(envp_to_change, "=", \
		&(str_to_join[pos_equal + 1]));
	free(envp_to_change);
	return (new_str);
}

char	*normi_supp_plus(char *begin, char *end, int pos_equal, int len)
{
	char	*new_str;

	begin[pos_equal - 1] = '\0';
	end[len - pos_equal] = '\0';
	new_str = ft_strjoin(begin, end);
	free(begin);
	free(end);
	return (new_str);
}

char	*secur_alloc_supp_plus(char *begin)
{
	free(begin);
	return (NULL);
}

void	normi_supp_plus_2(char *str, char *begin, char *end, int pos_equal)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (i < pos_equal - 1)
			begin[i] = str[i];
		else if (i >= pos_equal)
		{
			end[j] = str[i];
			j++;
		}
		i++;
	}
}
