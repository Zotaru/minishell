/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:18:31 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/29 19:02:56 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_alloc_files(t_cmd *cmd)
{
	int	i;

	i = -1;
	cmd->redir_in = 0;
	cmd->redir_out = 0;
	while (cmd->token[++i])
	{
		if (cmd->token[i][0] == '<')
			cmd->redir_in++;
		else if (cmd->token[i][0] == '>')
			cmd->redir_out++;
	}
	cmd->input_file = ft_calloc(sizeof(char *), (cmd->redir_in + 1));
	if (!cmd->input_file)
		return (0);
	cmd->output_file = ft_calloc(sizeof(char *), (cmd->redir_out + 1));
	if (!cmd->output_file)
		return (free(cmd->input_file), 0);
	cmd->hd = ft_calloc(sizeof(int), cmd->redir + 1);
	if (!cmd->hd)
		return (free(cmd->input_file), free(cmd->output_file), 0);
	return (1);
}

int	ft_fnm_len(char *str, int i, t_cmd *cmd)
{
	int	len;

	len = i;
	while (str[i] != ' ' && str[i] != '\t'
		&& str[i] != '<' && str[i] != '>' && str[i])
		i++;
	(void)cmd;
	return (i - len);
}

int	ft_search_name(t_cmd *cmd, char *str, int k, int z)
{
	static int	i = 0;
	static int	j = 0;
	int			n;

	if (!z)
	{
		i = 0;
		j = 0;
	}
	n = 0;
	if (!ft_strncmp(str + k, REDIR_RIGHT, 1)
		|| !ft_strncmp(str + k, REDIR_DOUBLE_RIGHT, 2))
	{
		ft_pass_space(str, &k, &n);
		cmd->output_file[j++] = ft_substr(str, k, ft_fnm_len(str, k, cmd));
	}
	else if (!ft_strncmp(str + k, REDIR_LEFT, 1))
	{
		ft_pass_space(str, &k, &n);
		cmd->input_file[i++] = ft_substr(str, k, ft_fnm_len(str, k, cmd));
	}
	return (k + ft_fnm_len(str, k, cmd) + n);
}

char	*ft_parse_redir(char *str, int i, int j, t_cmd *cmd)
{
	int		k;
	char	*tmp;
	char	*res;

	k = 0;
	res = ft_substr(str, 0, ft_next_redir(str, i) - i);
	while (1)
	{
		if (ft_check_parse_redir(str, i) && ft_get_state(str, i) == base)
		{
			i = ft_search_name(cmd, str, i, ++j - 1);
			if (j > k)
			{
				tmp = ft_substr(str, i, ft_next_redir(str, i) - i);
				res = ft_tjoin(res, tmp);
				free(tmp);
				k++;
			}
		}
		else
			i++;
		if (i >= (int)ft_strlen(str))
			break ;
	}
	return (res);
}

char	*ft_search_redir(char *str, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_parse_redir(str, i, j, cmd);
	return (free(str), res);
}
