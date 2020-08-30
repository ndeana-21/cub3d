/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:10:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/29 19:25:58 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		**ft_lsttodmas(t_list *lst, int *y)
{
	int		i;
	char	**dmas;

	if (!lst)
		return (NULL);
	*y = ft_lstsize(lst);
	if (!(dmas = (char **)malloc(ft_lstsize(lst) * sizeof(size_t))))
		return (NULL);
	i = 0;
	while (i < *y)
	{
		if (!(dmas[i++] = ft_strdup(lst->content)))
			return (NULL);
		lst = lst->next;
	}
	return (dmas);
}

char			*ft_strpass(char *str, char *sample)
{
	while (*str)
		if (ft_strchr(sample, *str))
			str++;
	return (str);
}

char			*find_sample(char *samples, char *str)
{
	char	*prob_out;
	int		i;
	int		j;

	i = 0;
	while (samples[i])
	{
		j = 0;
		while (samples[i + j] && str[j])
			if (samples[i + j] != str[j++])
				break;
		if (!samples[i + j])
		{
			if (!(prob_out = ft_strdup(&samples[i])))
				return (NULL);
			return (prob_out);
		}
		else
			while (samples[i + j])
				j++;
		i += j + 1;
	}
	return (NULL);
}

int			equal_map(t_list *map, int x)
{
	int		i;
	char	*tmp;

	if (!(map))
		return (print_error("ERROR equal_map - empty map\n"));
	while (1)
	{
		i = ft_strlen(map->content);
		if (i < x)
		{
			if (!(map->content = (char *)ft_realloc(map->content, sizeof(char) * x + 1)))
				return (print_error("allocation ERROR\n"));
			while (i < x)
				((char *)map->content)[i++] = ' ';
			((char *)map->content)[i] = 0;
		}
		map = map->next;
		if (!map)
			break ;
	}
	return (1);
}

t_list			*file_reader(char *file)
{
	t_list	*start_lst;
	t_list	*lst;
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	if (0 > (fd = open(file, O_RDONLY)))
		return (NULL);
	ret = ft_get_next_line(fd, &line);
	if (!(start_lst = ft_lstnew(line)))
		return (NULL);
	lst = start_lst;
	while (0 < ret)
	{
		ret = ft_get_next_line(fd, &line);
		if (!(lst->next = ft_lstnew(line)))
			return (NULL);
		lst = lst->next;
	}
	close(fd);
	if (ret < 0)
		return (NULL);
	return (start_lst);
}
