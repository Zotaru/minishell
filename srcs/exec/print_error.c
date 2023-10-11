/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:08:36 by alex              #+#    #+#             */
/*   Updated: 2023/08/09 17:19:45 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	int	original_stdout;
	int	original_stderr;

	original_stdout = dup(1);
	original_stderr = dup(2);
	dup2(2, 1);
	printf("%s", str);
	dup2(original_stdout, 1);
	dup2(original_stderr, 2);
	close(original_stderr);
	close(original_stdout);
	return ;
}
