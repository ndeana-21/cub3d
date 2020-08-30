/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:16:09 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/30 01:54:24 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				print_error(char *error)
{
	perror(error);
	return (-1);
}

int		arg_error(int argc, char **argv, t_cub3d *cub3d)
{
	int		len;

	if (argc < 2)
		return (print_error("ERROR too few args\n"));
	else if (argc > 3)
		return (print_error("ERROR too many args\n"));
	else if (argc == 3)
	{
		if (!(ft_strncmp(argv[2], "--save", 7)))
			cub3d->save = 1;
		else
			return (print_error("ERROR unknown arg\n"));
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || '.' != argv[1][len - 4] ||
			'b' != (ft_strncmp(&argv[1][len - 4], ".cub", 4)))
		return (print_error("ERROR filename doesn't end with the `.cub`\n"));
	if (!(cub3d->map->map_path = ft_strdup(argv[1])))
		return (print_error("allocation ERROR\n"));
	return (1);
}

void 		debug_print(t_cub3d *cub3d)//
{
	printf("\n\n-------------DEBUG--------------\n");
	printf("====cub3d====\n");
	printf("res x:%d y:%d\nsave:%d\n", cub3d->res_x, cub3d->res_y, cub3d->save);
	printf("=====map=====\n");
	printf("map_path: %s\nmap x:%d y:%d\n==============map_start===========\n",
			cub3d->map->map_path, cub3d->map->map_x, cub3d->map->map_y);
	int y = 0;
	while (y < cub3d->map->map_y)
	{
		printf("|%s|\n", cub3d->map->map[y]);
		y++;
	}
	printf("===============map_end============\n");
	printf("====player====\n");
	printf("exist = %d\npow = %lf\nplayer x:%lf y:%lf\n",
			cub3d->map->player->exist, cub3d->map->player->pow,
			cub3d->map->player->x_pos, cub3d->map->player->y_pos);
	printf("====textures==== count = %d\n", cub3d->map->texture->texture_count);
	while (cub3d->map->texture->texture_count)
		printf("sample - %s\npath - %s\n",
			cub3d->map->texture->name_path[cub3d->map->texture->texture_count],
			cub3d->map->texture->texture_path[(cub3d->map->texture->texture_count)--]);
	printf("====colors==== count = %d\n", cub3d->map->texture->trgb_count);
	while (cub3d->map->texture->trgb_count)
		printf("sample - %s\ntrgb - %d",
			cub3d->map->texture->name_trgb[cub3d->map->texture->trgb_count],
			cub3d->map->texture->trgb[(cub3d->map->texture->trgb_count)--]);
}
