/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:38:21 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 15:24:52 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			find_color_cf(t_cub *cub, t_walls *walls, t_colorlst *color)
{
	t_colorlst	*tmp;

	tmp = color;
	while (tmp)
	{
		if (tmp->name)
		{
			if ((int)ft_strlen(FLOOR_SAMPLE) ==
				ft_strcmp(FLOOR_SAMPLE, tmp->name))
				walls->floor = tmp->trgb;
			else if ((int)ft_strlen(CELLING_SAMPLE) ==
					ft_strcmp(CELLING_SAMPLE, tmp->name))
				walls->celling = tmp->trgb;
		}
		else
			print_error(cub, "CUB_ERROR no color for floor or celling");
		tmp = (t_colorlst *)tmp->next;
	}
	if ((0 > walls->floor) || (0 > walls->celling))
		print_error(cub, "CUB_ERROR no color for floor or celling");
}

int				count_sprites(t_map *map, char sample)
{
	t_point		point;
	long		count;

	point.y = -1;
	count = 0;
	while (++point.y < (double)map->res.y)
	{
		point.x = -1;
		while (++point.x < (double)map->res.x)
			if (map->map[(int)point.y][(int)point.x] == sample)
				count++;
		if (count >= INT_MAX)
			return (-1);
	}
	return ((int)count);
}

t_img			*find_img(t_pathlst *path, char *str)
{
	t_pathlst	*path_current;

	path_current = path;
	while (path_current)
	{
		if ((int)ft_strlen(str) ==
			ft_strcmp(str, path_current->name))
			return (path_current->img);
		path_current = (t_pathlst *)path_current->next;
	}
	return (NULL);
}
