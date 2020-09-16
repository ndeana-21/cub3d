/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:46:58 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/14 18:08:16 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub			*cub3d_init()
{
	t_cub *cub;

	if (!(cub = malloc(sizeof(t_cub))) ||
		!(cub->map = malloc(sizeof(t_map))) ||
		!(cub->data = malloc(sizeof(t_data))) ||
		!(cub->map->walls = malloc(sizeof(t_walls))) ||
		!(cub->map->img = malloc(sizeof(t_parsed))))
	{
		print_error("");
		return (NULL);
	}
	if (!(cub->mlx = mlx_init()))
	{
		print_error("MLX_ERROR mlx initialisation");
		return (NULL);
	}
	cub->map->map = NULL;
	cub->map->res.x = 0;
	cub->map->res.y = 0;
	cub->save = 0;
	return (cub);
}
