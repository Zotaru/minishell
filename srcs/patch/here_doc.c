/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:33:37 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 21:28:50 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files_hd(int *pos, t_mini *minsh, char **name, int *fd)
{
	*name = create_random_name(minsh, pos);
	*fd = open(*name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*fd == -1)
	{
		perror(*name);
		free(*name);
		free_t_mini(minsh);
		exit(1);
	}
}

void	rl_hd(t_cmd *cmd, int *pos, t_mini *minsh, int fd)
{
	char		*temp;
	int			len_limiter;

	len_limiter = ft_strlen((cmd->input_file)[pos[2]]);
	while (1)
	{
		temp = read_next_line(0);
		if (!temp)
			break ;
		if (ft_strncmp(temp, (cmd->input_file)[pos[2]], len_limiter) == 0
			&& temp[len_limiter] == '\n')
			break ;
		if (ft_strncmp(temp, (cmd->input_file)[pos[2]], len_limiter) == 0
			&& temp[len_limiter] == '\0')
			break ;
		if ((cmd->hd)[pos[1]] == 0)
			temp = ft_dol_search_bis(temp, minsh->envp);
		ft_putstr_fd(temp, fd);
		ft_putchar_fd('\n', fd);
		free(temp);
	}
	if (temp)
		free(temp);
}

void	here_doc(t_cmd *cmd, int *pos, t_mini *minsh)
{
	char	*name;
	int		fd;

	open_files_hd(pos, minsh, &name, &fd);
	minsh->act_fd = fd;
	stat_pointer_char(name);
	rl_hd(cmd, pos, minsh, fd);
	close(fd);
	free((cmd->input_file)[pos[2]]);
	(cmd->input_file)[pos[2]] = name;
	minsh->act_fd = -1;
	return ;
}
