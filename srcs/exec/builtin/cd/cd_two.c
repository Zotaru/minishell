/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_two.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:10:53 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/09 18:11:48 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_in_env_for_cd(t_mini *minsh, char *sjoin, char *pref, char *sfree)
{
	char	**new_env;
	int		size;
	int		i;

	i = -1;
	size = size_double_tab((minsh->envp));
	new_env = malloc((size + 1 + 1) * sizeof(char *));
	if (new_env == NULL)
		ft_free_one(sfree, sjoin, minsh);
	while ((minsh->envp)[++i])
	{
		new_env[i] = ft_strdup((minsh->envp)[i]);
		if (new_env[i] == NULL)
		{
			free_double_tab_char(new_env);
			free(sfree);
			free(sjoin);
			free_t_mini(minsh);
			exit(1);
		}
	}
	new_env[i++] = ft_strjoin(pref, sjoin);
	new_env[i] = NULL;
	free_double_tab_char(minsh->envp);
	minsh->envp = new_env;
}

void	update_pwd_add_oldpwd(t_mini *minsh, char *s_new, char *s_old)
{
	int	i;

	i = check_in_env("PWD=", 4, minsh);
	free((minsh->envp)[i]);
	(minsh->envp)[i] = ft_strjoin("PWD=", s_new);
	add_in_env_for_cd(minsh, s_old, "OLDPWD=", s_new);
}

void	update_oldpwd_add_pwd(t_mini *minsh, char *s_new, char *s_old)
{
	int	i;

	i = check_in_env("OLDPWD=", 4, minsh);
	free((minsh->envp)[i]);
	(minsh->envp)[i] = ft_strjoin("OLDPWD=", s_old);
	add_in_env_for_cd(minsh, s_new, "PWD=", s_old);
}

void	add_both_in_env(t_mini *minsh, char *s_new, char *s_old)
{
	add_in_env_for_cd(minsh, s_new, "PWD=", s_old);
	add_in_env_for_cd(minsh, s_old, "OLDPWD=", s_new);
}

void	update_or_create_env(t_mini *minsh, char *s_new, char *s_old)
{
	int	checker;

	checker = check_for_create_env(minsh);
	if (checker == 0)
		update_pwd_add_oldpwd(minsh, s_new, s_old);
	if (checker == 1)
		update_oldpwd_add_pwd(minsh, s_new, s_old);
	if (checker == -1)
		add_both_in_env(minsh, s_new, s_old);
	return ;
}
