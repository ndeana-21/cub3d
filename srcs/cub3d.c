/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:46:58 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 15:25:17 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img			*img_init(t_cub *cub)
{
	t_img	*img;

	img = NULL;
	img = malloc(sizeof(t_img));
	if (!img)
		print_error(cub, "ERROR malloc");
	*img = (t_img){NULL, 0, 0};
	img->data = malloc(sizeof(t_data));
	if (!img->data)
	{
		free(img);
		print_error(cub, "ERROR malloc");
	}
	*img->data = (t_data){NULL, NULL, 0, 0, 0};
	return (img);
}

static t_wall	*wall_init(t_cub *cub)
{
	t_wall	*wall;

	wall = NULL;
	wall = malloc(sizeof(t_wall));
	if (!wall)
		print_error(cub, "ERROR malloc");
	wall->vec = (t_vec){(t_point){0, 0}, (t_point){0, 0}};
	wall->next_wall = NULL;
	return (wall);
}

static void		walls_init(t_cub *cub, t_map *map)
{
	map->walls = malloc(sizeof(t_walls));
	if (!cub->map->walls)
		print_error(cub, "ERROR malloc");
	*map->walls = (t_walls){NULL, NULL, NULL, NULL,
							NULL, NULL, NULL, NULL, -1, -1};
	map->walls->east = wall_init(cub);
	map->walls->west = wall_init(cub);
	map->walls->north = wall_init(cub);
	map->walls->south = wall_init(cub);
}

static void		map_init(t_cub *cub)
{
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		print_error(cub, "ERROR malloc");
	*cub->map = (t_map){(t_res){0, 0}, 0,
				NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	cub->map->img = malloc(sizeof(t_parsed));
	if (!cub->map->img)
		print_error(cub, "ERROR malloc");
	*cub->map->img = (t_parsed){NULL, malloc(sizeof(t_colorlst))};
	if (!cub->map->img->color)
		print_error(cub, "ERROR malloc");
	*cub->map->img->color = (t_colorlst){NULL, -1, NULL};
	walls_init(cub, cub->map);
	cub->map->sprite = malloc(sizeof(t_sprites));
	if (!cub->map->sprite)
		print_error(cub, "ERROR malloc");
	*cub->map->sprite = (t_sprites){NULL, NULL};
}

t_cub			*cub3d_init(void)
{
	t_cub	*cub;

	cub = NULL;
	cub = malloc(sizeof(t_cub));
	if (!cub)
		print_error(cub, "ERROR malloc");
	*cub = (t_cub){NULL, NULL, NULL, 0, (t_res){0, 0},
		(t_key){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, NULL};
	cub->mlx = mlx_init();
	cub->data = malloc(sizeof(t_data));
	if (!cub->data)
		print_error(cub, "ERROR malloc");
	*cub->data = (t_data){NULL, NULL, 0, 0, 0};
	if (!cub->mlx)
		print_error(cub, "MLX_ERROR mlx initialisation");
	map_init(cub);
	return (cub);
}
