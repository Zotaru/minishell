/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:39:26 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/23 12:18:14 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_path(t_mini *mini)
{
	char	**tmp;

	if (!(mini->envp))
		return (NULL);
	tmp = mini->envp;
	if (!*tmp)
		return (NULL);
	while (ft_strncmp("PATH", *tmp, 4))
	{
		tmp++;
		if (!*tmp)
			return (NULL);
	}
	return (ft_split(*tmp + 5, ':'));
}

char	*ft_get_exe(char **path, char *cmd)
{
	char	*temp;
	char	*try;
	int		i;

	i = -1;
	if (!access(cmd, F_OK))
		return (NULL);
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		try = ft_strjoin(temp, cmd);
		if (!access(try, F_OK))
			return (free(try), temp);
		free(try);
		free(temp);
	}
	return (NULL);
}

void	ft_search_path(t_mini *mini, int n)
{
	int		i;
	char	**path;

	i = -1;
	path = ft_get_path(mini);
	if (!path)
		return ;
	while (++i < n)
		if (mini->cmds[i].cmd)
			if (mini->cmds[i].cmd[0])
				mini->cmds[i].path = ft_get_exe(path, mini->cmds[i].cmd[0]);
	ft_clean_split(path);
}
