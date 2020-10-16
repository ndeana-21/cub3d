/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:32:59 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/12 23:44:53 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			window_valid(t_cub *cub)
{
	int		size_x;
	int		size_y;

	mlx_get_screen_size(cub->mlx, &size_x, &size_y);
	if (cub->res.x > size_x)
		cub->res.x = size_x;
	if (cub->res.y > size_y)
		cub->res.y = size_y;
}

t_list			*file_reader(t_cub *cub, char *file)
{
	t_list	*start_lst;
	t_list	*lst;
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	if (0 > (fd = open(file, O_RDONLY)))
		print_error(cub, "ERROR can't open file .cub");
	ret = ft_get_next_line(fd, &line);
	if (!(start_lst = ft_lstnew(line)))
		print_error(cub, "ERROR malloc");
	lst = start_lst;
	while (0 < ret)
	{
		ret = ft_get_next_line(fd, &line);
		if (!(lst->next = ft_lstnew(line)))
			print_error(cub, "ERROR malloc");
		lst = (t_list *)lst->next;
		lst->next = NULL;
	}
	close(fd);
	if (ret < 0)
		return (NULL);
	return (start_lst);
}

char			*ft_strpass(char *str, char *sample)
{
	while (*str)
	{
		if (ft_strchr(sample, *str))
			str++;
		else
			return (str);
	}
	return (str);
}

char			*ft_findsample(t_cub *cub, char *samples, char *str)
{
	char	*sample_out;
	int		i;
	int		j;

	i = 0;
	while (samples[i])
	{
		j = -1;
		while (str[++j] && samples[i + j])
			if (samples[i + j] != str[j])
				break ;
		if (!samples[i + j])
		{
			if (!(sample_out = ft_strdup(&samples[i])))
				print_error(cub, "ERROR malloc");
			return (sample_out);
		}
		else
			while (samples[i + j])
				j++;
		i += j + 1;
	}
	return (NULL);
}
