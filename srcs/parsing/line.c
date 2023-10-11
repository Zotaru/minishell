/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:36:23 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 22:38:42 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fn_hd(t_cmd *cmd, int *l, int i, char **env)
{
	if (cmd->redir_type[i] == redir_double_left)
	{
		if (ft_strchr(cmd->input_file[*l], '\'')
			|| ft_strchr(cmd->input_file[*l], '\"'))
			cmd->hd[i] = 1;
		cmd->input_file[*l] = ft_wo_quote(cmd->input_file[*l]);
	}
	else
	{
		ft_to_expand(cmd->input_file[*l], cmd);
		cmd->input_file[*l] = ft_wo_quote(cmd->input_file[*l]);
		cmd->input_file[*l] = ft_dol_search(cmd->input_file[*l], \
			env, cmd, &cmd->hd[i]);
		free(cmd->to_expand);
		free(cmd->var_len);
	}
	(*l)++;
}

static void	ft_fn(t_cmd *cmd, char **env)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = -1;
	k = 0;
	l = 0;
	while (++i < cmd->redir)
	{
		j = 0;
		if (cmd->redir_type[i] == redir_double_right
			|| cmd->redir_type[i] == redir_right)
		{
			ft_to_expand(cmd->output_file[k++], cmd);
			cmd->output_file[k - 1] = ft_wo_quote(cmd->output_file[k - 1]);
			cmd->output_file[k - 1] = \
			ft_dol_search(cmd->output_file[k - 1], env, cmd, &j);
			free(cmd->to_expand);
			free(cmd->var_len);
		}
		else if (cmd->redir_type[i] == redir_double_left
			|| cmd->redir_type[i] == redir_left)
			ft_fn_hd(cmd, &l, i, env);
	}
}

static void	ft_cmd(t_cmd *cmd, char **env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!cmd->cmd)
	{
		free(cmd->to_expand);
		free(cmd->var_len);
		ft_fn(cmd, env);
		return ;
	}
	while (cmd->cmd[++i])
	{
		cmd->cmd[i] = ft_wo_quote(cmd->cmd[i]);
		cmd->cmd[i] = ft_dol_search(cmd->cmd[i], env, cmd, &j);
	}
	free(cmd->to_expand);
	free(cmd->var_len);
	ft_fn(cmd, env);
}

int	ft_cmds(char **cmd, t_cmd *cmds, char **env)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		ft_check_elements(cmd[i], &cmds[i]);
		ft_alloc_files(&cmds[i]);
		cmd[i] = ft_search_redir(cmd[i], &cmds[i]);
		ft_to_expand(cmd[i], &cmds[i]);
		cmds[i].cmd = ft_cmd_split(cmd[i], " ");
		ft_cmd(&cmds[i], env);
		free(cmd[i]);
	}
	return (free(cmd), i);
}

int	ft_line(char *line, t_mini *mini)
{
	int		i;
	char	**cmd;

	if (!ft_check_prompt(line))
		return (-1);
	if (!ft_triple(line))
		return (-1);
	cmd = ft_cmd_split(line, "|");
	mini->cmds = (t_cmd *)ft_calloc(sizeof(t_cmd), (ft_split_len(cmd) + 1));
	i = ft_cmds(cmd, mini->cmds, mini->envp);
	if (!ft_check_redir(mini, i))
		return (-1);
	ft_search_path(mini, i);
	return (i);
}
