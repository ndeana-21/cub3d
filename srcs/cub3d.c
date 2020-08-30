/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:46:58 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/28 17:19:45 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_cub3d	*cub3d_alloc()
{
	t_cub3d *cub3d;

	if (!(cub3d = malloc(sizeof(t_cub3d))) ||
		!(cub3d->map = malloc(sizeof(t_map))) ||
		!(cub3d->data = malloc(sizeof(t_data))) ||
		!(cub3d->map->player = malloc(sizeof(t_texture))) ||
		!(cub3d->map->texture = malloc(sizeof(t_player))) ||
		!(cub3d->map->texture->trgb = (int *)malloc(sizeof(int *))) ||
		!(cub3d->map->texture->name_path = (char **)malloc(sizeof(char **))) ||
		!(cub3d->map->texture->name_trgb = (char **)malloc(sizeof(char **))) ||
		!(cub3d->map->texture->texture_path = (char **)malloc(sizeof(char **))))
	{
		print_error("allocation ERROR\n");
		return (NULL);
	}
	if (!(cub3d->mlx = mlx_init()))
	{
		print_error("ERROR mlx initialisation\n");
		return (NULL);
	}
	return (cub3d);
}

t_cub3d			*cub3d_init()
{
	t_cub3d *cub3d;

	if (!(cub3d = cub3d_alloc()))
		return (NULL);
	cub3d->map->texture->texture_count = 0;
	cub3d->map->texture->trgb_count = 0;
	cub3d->map->player->exist = 0;
	cub3d->map->player->x_pos = 0;
	cub3d->map->player->y_pos = 0;
	cub3d->map->player->pow = 0;
	cub3d->map->map_x = 0;
	cub3d->map->map_y = 0;
	cub3d->res_x = 0;
	cub3d->res_y = 0;
	cub3d->save = 0;
	return (cub3d);
}
