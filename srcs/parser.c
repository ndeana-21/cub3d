/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:53:52 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/14 18:10:02 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		parse_color(t_parsed *img, char *str)
{
	char	*sample;
	int		trgb;

	str = ft_strpass(str, " ");
	if (!(sample = ft_findsample(COLOR_SAMPLE, str)))
		return (0);
	if (color_reptcheck(img->color, sample))
	{
		free(sample);
		return (print_error("CUB_ERROR some sample of color is repeat"));
	}
	str = ft_strpass(str += ft_strlen(sample), " ");
	trgb = set_r(0, ft_atoi(str));
	str = ft_strpass(ft_strpass(str, "0123456789"), " ");
	str = ft_strpass(*str == ',' ? str + 1 : str, " ");
	trgb = set_g(trgb, ft_atoi(str));
	str = ft_strpass(ft_strpass(str, "0123456789"), " ");
	str = ft_strpass(*str == ',' ? str + 1 : str, " ");
	trgb = set_b(trgb, ft_atoi(str));
	img->color = colorlst_append(img->color, sample, trgb);
	return (1);
}

static int		parse_path(t_cub *cub, char *str)
{
	char	*sample;
	char	*trimmed;
	int		fd;

	str = ft_strpass(str, " ");
	if (!(sample = ft_findsample(IMG_SAMPLE, str)))
		return (0);
	if (path_reptcheck(cub->map->img->path, sample))
	{
		free(sample);
		return (print_error("CUB_ERROR some sample of path is repeat"));
	}
	str += ft_strlen(sample);
	trimmed = ft_strtrim(str, " ");
	if (0 > (fd = open(trimmed, O_RDONLY)))
	{
		free(trimmed);
		free(sample);
		return (print_error(""));
	}
	close(fd);
	if (0 > (pathlst_append(cub, sample, trimmed)))
		return (-1);
	return (1);
}

static int		parse_res(t_cub *cub, char *str)
{
	str = ft_strpass(str, " ");
	if (!(str = check_sample(RES_SAMPLE, str)))
		return (0);
	if (!(cub->res.x = ft_atoi(str)) || (0 > cub->res.x))
		return (print_error("ERROR invalid resolution\n"));
	str = ft_strpass(ft_strpass(str, " "), "0123456789");
	if (!(cub->res.y = ft_atoi(str)) || (0 > cub->res.y))
		return (print_error("ERROR invalid resolution\n"));
	return (window_valid(cub));
}

static int		parser_branch(t_cub *cub, t_list *lst)
{
	int		ret;
	
	if (!cub->res.x)
	{
		if (ret = parse_res(cub, lst->content))
			return (ret);
	}
	else if (ret = parse_path(cub, lst->content))
		return (ret);
	else if (ret = parse_color(cub->map->img, lst->content))
		return(ret);
	else if (!*(ft_strpass(lst->content, " ")))
		return(0);
	else if (!cub->map->player)
	{
		if (ret = parse_map(cub->map, lst))
			if (ret < 0)
				return (ft_pagedel(&cub->map, cub->map->res.y));
		return(ret);
	}
	return(print_error("ERROR invalid file contents"));
}

int				parser(t_cub *cub)
{
	t_list	*lst;
	int		ret;

	lst = file_reader(cub->map->map_path);
	if (!lst)
		return (print_error("ERROR empty file"));
	while (lst)
	{
		if (0 > (ret = parser_branch(cub, lst)))
			return (ret);
		if (ret == 2)
			lst = ft_lstnnext(lst, cub->map->res.y - 1);
		if (!lst->next)
		{
			if (!cub->map->player || !cub->res.x ||
				!cub->map->img->color || !cub->map->img->path)
				return(print_error("ERROR not enough args"));
		}
		lst = lst->next;
	}
	ft_lstclear(&lst, free);
	return (0);
}
