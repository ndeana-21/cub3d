/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:53:52 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 14:57:48 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		parse_color(t_cub *cub, t_parsed *img, char *str)
{
	char	*sample;

	str = ft_strpass(str, " ");
	sample = NULL;
	if (!(sample = ft_findsample(cub, COLOR_SAMPLE, str)))
		return ;
	if (color_reptcheck(img->color, sample))
	{
		free(sample);
		print_error(cub, "CUB_ERROR some sample of color is repeat");
	}
	if (!ft_isdigit(*(str = ft_strpass(str += ft_strlen(sample), " "))))
		print_error(cub, "CUB_ERROR invalid color");
	img->color = colorlst_append(img->color, sample, valid_color(cub, str));
}

static void		parse_path(t_cub *cub, char *str)
{
	char	*sample;
	char	*trimmed;

	str = ft_strpass(str, " ");
	if (!(sample = ft_findsample(cub, IMG_SAMPLE, str)))
		return ;
	if (path_reptcheck(cub->map->img->path, sample) ||
		!(str = ft_strpass(str += ft_strlen(sample), " ")))
	{
		free(sample);
		if (!str)
			print_error(cub, "CUB_ERROR have no path");
		print_error(cub, "CUB_ERROR some sample of path is repeat");
	}
	if (ft_strchr(trimmed = ft_strtrim(str, " "), ' '))
		print_error(cub, "CUB_ERROR invalid path");
	pathlst_append(cub, sample, trimmed);
}

static void		parse_res(t_cub *cub, char *str)
{
	str = ft_strpass(str, " ");
	if (!(str = check_sample(RES_SAMPLE, str)))
		return ;
	if (!(cub->res.x = ft_atoi(str)) || (0 > cub->res.x))
		print_error(cub, "ERROR invalid resolution");
	str = ft_strpass(ft_strpass(str, " "), "0123456789");
	if (!(cub->res.y = ft_atoi(str)) || (0 > cub->res.y))
		print_error(cub, "ERROR invalid resolution");
	if (*(str = ft_strpass(ft_strpass(
							ft_strpass(str, " "), "0123456789"), " ")))
		print_error(cub, "ERROR invalid resolution");
	window_valid(cub);
}

static int		parser_branch(t_cub *cub, t_list *lst)
{
	int		ret;

	if (!cub->res.x || !cub->res.y)
		parse_res(cub, lst->content);
	parse_path(cub, lst->content);
	parse_color(cub, cub->map->img, lst->content);
	if (!*(ft_strpass(lst->content, " ")))
		return (0);
	if (!cub->map->player)
	{
		ret = parse_map(cub, cub->map, lst);
		return (ret);
	}
	return (print_error(cub, "ERROR invalid file contents"));
}

int				parser(t_cub *cub)
{
	t_list	*lst;
	t_list	*lst_start;
	int		ret;

	lst = file_reader(cub, cub->map->map_path);
	ret = 0;
	if (!lst)
		print_error(cub, "ERROR empty file");
	lst_start = lst;
	while (lst)
	{
		if (0 > (ret = parser_branch(cub, lst)))
			return (ret);
		if (ret == 2)
			lst = ft_lstnnext(lst, cub->map->res.y - 1);
		if (!lst->next)
			if (!cub->map->player || !cub->res.x || !cub->map->img->path)
				print_error(cub, "ERROR not enough args");
		lst = lst->next;
	}
	ft_lstclear(lst_start, free);
	return (FALSE);
}
