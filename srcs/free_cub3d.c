/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:33:34 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 03:22:48 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_pathlst(t_pathlst *path)
{
	while (path)
	{
		free(path->name);
		free(path->img);
		free(path);
		path = path->next;
	}
}

void		*free_sprites(t_sprites *sprites)
{
	while (sprites)
	{
		free(sprites);
		sprites = sprites->next_sprite;
	}
	return (NULL);
}

void		*free_wall(t_wall *wall)
{
	while (wall)
	{
		free (wall);
		wall = wall->next_wall;
	}
	return (NULL);
}

static void	free_lsts(t_sprites *sprite, t_ray *ray,
							t_walls *walls, t_colorlst *color)
{
	while (sprite)
	{
		free (sprite);
		sprite = sprite->next_sprite;
	}
	while (ray)
	{
		free (ray);
		ray = ray->next_ray;
	}
	while (color)
	{
		free(color->name);
		free(color);
		color = color->next;
	}
	free_wall(walls->north);
	free_wall(walls->south);
	free_wall(walls->east);
	free_wall(walls->west);
	free(walls);
}

void			free_cub(t_cub *cub)
{
	free(cub->mlx);
	free(cub->map->player);
	free(cub->map->map_path);
	while (cub->map->res.y)
		free(cub->map->map[--cub->map->res.y]);
	free(cub->map->map);
	free_lsts(cub->map->sprites, cub->map->ray,
			cub->map->walls, cub->map->img->color);
	free_pathlst(cub->map->img->path);
	free(cub->map->img);
	free(cub->data);
	free(cub->map);
	free(cub);
}
