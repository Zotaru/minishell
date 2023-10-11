/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:20:37 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/04 17:44:12 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_fill_from_lst(t_glist *lst)
{
	int		i;
	int		j;
	int		length;
	char	*tab;

	length = ft_listiter(lst, &ft_check_sep);
	tab = malloc((length + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (lst)
	{
		while (i < length && lst->content[j])
		{
			tab[i] = lst->content[j];
			i++;
			j++;
		}
		j = 0;
		lst = lst->next;
	}
	tab[i] = '\0';
	return (tab);
}

char	*length_diff_zero(char *buf, char *kanye, int length, t_glist **lst)
{
	int		i;
	int		j;
	char	*temp;

	j = -1;
	i = ft_check_sep(buf, '\n', 0) + 1;
	temp = malloc((i + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (++j < i)
		temp[j] = buf[j];
	temp[j] = '\0';
	ft_listadd_back(lst, ft_listnew(temp, 0, 1), 0);
	free(temp);
	i = 0;
	kanye = malloc((length - j + 1) * sizeof(char));
	if (kanye == NULL)
		return (NULL);
	while (j < length)
		kanye[i++] = buf[j++];
	kanye[i] = '\0';
	if (kanye[0] == '\0')
		return (free(kanye), NULL);
	return (kanye);
}

char	*ret_line_in_static2(char *kanye, t_glist **lst)
{
	char	*temp;
	int		i;
	int		j;

	i = ft_check_sep(kanye, '\n', 0) + 1;
	j = -1;
	temp = malloc((i + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (++j < i)
		temp[j] = kanye[j];
	temp[j] = '\0';
	ft_listadd_back(lst, ft_listnew(temp, 0, 1), 0);
	free(temp);
	j = 0;
	while (kanye[i])
		kanye[j++] = kanye[i++];
	kanye[j] = '\0';
	if (kanye[0] == '\0')
		return (free(kanye), NULL);
	return (kanye);
}

t_glist	*get_next_line2(int fd)
{
	static char	*kanye = NULL;
	char		*buffer;
	t_glist		*lst;
	int			tab_fd_l[3];

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || buffer == NULL)
		return (free(buffer), NULL);
	lst = NULL;
	if (kanye != NULL && ft_check_sep(kanye, '\n', 0) >= 0)
		kanye = ret_line_in_static2(kanye, &lst);
	else
	{
		tab_fd_l[0] = -2;
		if (kanye != NULL && ft_check_sep(kanye, '\n', 0) == -1)
			kanye = ft_normi(kanye, buffer, &lst, tab_fd_l);
		tab_fd_l[1] = read(fd, buffer, BUFFER_SIZE);
		if ((tab_fd_l[1] == 0 && lst == NULL) || tab_fd_l[1] < 0)
			return (free(buffer), NULL);
		buffer[tab_fd_l[1]] = '\0';
		tab_fd_l[0] = fd;
		if (tab_fd_l[1] != 0)
			kanye = ft_normi(kanye, buffer, &lst, tab_fd_l);
	}
	return (free(buffer), lst);
}

char	*get_next_line(int fd)
{
	char	*tab_fin;
	t_glist	*lst;

	lst = get_next_line2(fd);
	if (lst == NULL)
		return (NULL);
	tab_fin = ft_fill_from_lst(lst);
	ft_listadd_back(&lst, NULL, 1);
	return (tab_fin);
}
