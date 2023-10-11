/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_triple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:54:52 by alex              #+#    #+#             */
/*   Updated: 2023/08/09 17:18:30 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_triple(char *str1, char *str2, char *str3)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(str1, str2);
	if (temp == NULL)
		return (NULL);
	final = ft_strjoin(temp, str3);
	if (final == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (final);
}
