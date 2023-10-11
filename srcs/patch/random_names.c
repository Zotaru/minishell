/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_names.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:37:13 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/05 15:45:45 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_rand_name_bis(int *pos)
{
	char	*first;
	char	*second;
	char	*res;

	first = ft_itoa(pos[0]);
	if (!first)
		return (NULL);
	second = ft_itoa(pos[1]);
	if (!second)
		return (free(first), NULL);
	res = ft_strjoin(first, second);
	return (free(first), free(second), res);
}

char	*create_rand_name_with_int(int *pos)
{
	char	*first_second;
	char	*third;
	char	*str;

	first_second = create_rand_name_bis(pos);
	if (!first_second)
		return (NULL);
	third = ft_itoa(pos[2]);
	if (!third)
		return (free(first_second), NULL);
	str = ft_strjoin(first_second, third);
	free(first_second);
	free(third);
	return (str);
}

void	create_str_and_numb(t_mini *minsh, int *pos, char **str, char **numb)
{
	*str = ft_strdup("/tmp/rand");
	if (*str == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	*numb = create_rand_name_with_int(pos);
	if (*numb == NULL)
	{
		free(*str);
		free_t_mini(minsh);
		exit(1);
	}
}

char	*create_random_name(t_mini *minsh, int *pos)
{
	char	*str;
	char	*numb;
	char	*final;

	create_str_and_numb(minsh, pos, &str, &numb);
	final = ft_strjoin(str, numb);
	if (final == NULL)
	{
		free(str);
		free(numb);
		free_t_mini(minsh);
		exit(1);
	}
	free(str);
	free(numb);
	return (final);
}
