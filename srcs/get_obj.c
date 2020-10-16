/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:39:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/16 18:40:45 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				check_side(t_map *map, t_point point, char side, char *sample)
{
	if (side == 'N' && (((int)point.y + 1) < map->res.y))
	{
		if (ft_strchr(sample, map->map[(int)point.y + 1][(int)point.x]))
			return (TRUE);
	}
	else if (side == 'S' && (((int)point.y - 1) >= 0))
	{
		if (ft_strchr(sample, map->map[(int)point.y - 1][(int)point.x]))
			return (TRUE);
	}
	else if (side == 'E' && (((int)point.x - 1) >= 0))
	{
		if (ft_strchr(sample, map->map[(int)point.y][(int)point.x - 1]))
			return (TRUE);
	}
	else if (side == 'W' && (((int)point.x + 1) < map->res.x))
		if (ft_strchr(sample, map->map[(int)point.y][(int)point.x + 1]))
			return (TRUE);
	return (FALSE);
}

static void		horizontal_wall_init(t_cub *cub, t_wall *wall,
									double plus_y, char side)
{
	t_point	point;
	t_wall	*tmp_lst;

	tmp_lst = wall;
	point.y = -1;
	while (++point.y < cub->map->res.y)
	{
		point.x = -1;
		while (++point.x < cub->map->res.x)
			if (ft_strchr("1", cub->map->map[(int)point.y][(int)point.x]) &&
				check_side(cub->map, point, side, NO_VISION))
			{
				tmp_lst->next_wall = malloc(sizeof(t_wall));
				if (!tmp_lst->next_wall)
					print_error(cub, "ERROR malloc");
				tmp_lst = (t_wall *)tmp_lst->next_wall;
				tmp_lst->vec.start = (t_point){point.x, point.y + plus_y};
				while (ft_strchr("1",
						cub->map->map[(int)point.y][(int)point.x]))
					point.x++;
				tmp_lst->vec.end = (t_point){point.x, point.y + plus_y};
			}
	}
	tmp_lst->next_wall = NULL;
}

static void		vertical_wall_init(t_cub *cub, t_wall *wall,
									double plus_x, char side)
{
	t_point	point;
	t_wall	*tmp_lst;

	tmp_lst = wall;
	point.x = -1;
	while (++point.x < cub->map->res.x)
	{
		point.y = -1;
		while (++point.y < cub->map->res.y)
			if (ft_strchr("1", cub->map->map[(int)point.y][(int)point.x]) &&
				check_side(cub->map, point, side, NO_VISION))
			{
				tmp_lst->next_wall = malloc(sizeof(t_wall));
				if (!tmp_lst->next_wall)
					print_error(cub, "ERROR malloc");
				tmp_lst = (t_wall *)tmp_lst->next_wall;
				tmp_lst->next_wall = NULL;
				tmp_lst->vec.start = (t_point){point.x + plus_x, point.y};
				while (ft_strchr("1",
						cub->map->map[(int)point.y][(int)point.x]))
					point.y++;
				tmp_lst->vec.end = (t_point){point.x + plus_x, point.y};
			}
	}
}

void			raw_to_obj_walls(t_cub *cub, t_map *map)
{
	map->walls->north->vec = make_vector(0, 0, map->res.x, 0);
	map->walls->south->vec = make_vector(0, map->res.y, map->res.x, map->res.y);
	map->walls->east->vec = make_vector(map->res.x, 0, map->res.x, map->res.y);
	map->walls->west->vec = make_vector(0, 0, 0, map->res.y);
	horizontal_wall_init(cub, map->walls->north, 1.0, 'N');
	horizontal_wall_init(cub, map->walls->south, 0.0, 'S');
	vertical_wall_init(cub, map->walls->east, 0.0, 'E');
	vertical_wall_init(cub, map->walls->west, 1.0, 'W');
	find_color_cf(cub, map->walls, map->img->color);
	map->walls->img_n = find_img(map->img->path, "NO ");
	map->walls->img_e = find_img(map->img->path, "EA ");
	map->walls->img_w = find_img(map->img->path, "WE ");
	map->walls->img_s = find_img(map->img->path, "SO ");
	if (!map->walls->img_n || !map->walls->img_s ||
		!map->walls->img_w || !map->walls->img_e)
		print_error(cub, "ERROR some img of walls = NULL");
}

void			raw_to_obj_sprite(t_cub *cub, t_map *map, char sample)
{
	t_point		point;
	int			max_spr;
	int			i;

	if (0 > (max_spr = count_sprites(map, sample)))
		print_error(cub, "ERROR too many sprites");
	if (!(map->sprite->spr = malloc(sizeof(t_sprite) * (max_spr + 1))))
		print_error(cub, "ERROR malloc");
	map->sprite->img = find_img(map->img->path, "S ");
	i = 0;
	point.y = -1;
	while (++point.y < (double)map->res.y)
	{
		point.x = -1;
		while (++point.x < (double)map->res.x)
			if (map->map[(int)point.y][(int)point.x] == sample)
				map->sprite->spr[i++] = (t_sprite){(t_point)
					{point.x + 0.5, point.y + 0.5}, 0, 0, 0, 0, 0};
		if (i == max_spr)
			break ;
	}
	map->sprite->spr[i].dst = -1;
}
