/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:35:29 by jehubert          #+#    #+#             */
/*   Updated: 2023/05/01 00:39:52 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_join(char *s1, char *s2)
{
	char	*res;

	res = ft_realloc(s1, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return ;
	ft_strlcat(res, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s2);
}
