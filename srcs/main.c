/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:52:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/30 02:07:24 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			print_lst(t_list *lst)
{
	while (1)
	{
		printf("|%p|\n", lst->content);
		lst = lst->next;
		if (!lst->next)
			break ;
	}
}

void			free_cub3d(t_cub3d **cub3d)
{
	if (!*cub3d)
		return ;
	free((*cub3d)->mlx);
	// free((*cub3d)->win);
	// free((*cub3d)->data->img);
	// free((*cub3d)->data->addr);
	free((*cub3d)->data);
	free((*cub3d)->map->player);
	free((*cub3d)->map->texture->img);
	// while ()
	// 	free((*cub3d)->map->texture->name_path);
	// while ()
	// 	free((*cub3d)->map->texture->name_trgb);
	// while ()
	// 	free((*cub3d)->map->texture->texture_path);
	free((*cub3d)->map->texture->trgb);
	free((*cub3d)->map->texture);
	free((*cub3d)->map->map_path);
	while ((*cub3d)->map->map_y)
		free((*cub3d)->map->map[(*cub3d)->map->map_y--]);
	free((*cub3d)->map);
	free((*cub3d));
}

int             main(int argc, char **argv)
{
	t_cub3d		*cub3d;
	t_list		*lst;

	if (!(cub3d = cub3d_init()) || 0 > arg_error(argc, argv, cub3d))
		return (0);
	lst = file_reader(cub3d->map->map_path);
	parse_map(cub3d->map, lst);
	// printf("%c\n", cub3d->map->map[7][0]);
	// printf("(%d)\n", scan_around(cub3d->map, 7,0));
	if (map_validator(cub3d->map))
		printf("\nMap valid\n");
	else
		printf("\nMap INvalid\n");
	debug_print(cub3d);

	// ft_lstclear(lst, free);
	// free_cub3d(&cub3d);

	
    // cub3d->win = mlx_new_window(
	// 				cub3d->mlx, cub3d->res_x, cub3d->res_y, "cub3D");
    // cub3d->data->img = mlx_new_image(cub3d->mlx, cub3d->res_x, cub3d->res_y);
    // cub3d->data->addr = mlx_get_data_addr(cub3d->data->img,
	// 									&cub3d->data->bits_per_pixel,
	// 									&cub3d->data->line_length,
	// 									&cub3d->data->endian);

	// mlx_hook(cub3d->win, 2, 1L<<0, keycode_print, cub3d);
	// mlx_hook(cub3d->win, 2, 1L<<0, hook_close, cub3d);
	// mlx_hook(cub3d->win, 4, 1L<<2, keycode_print, cub3d);
	// mlx_loop_hook(cub3d->mlx, render_next_frame, cub3d);
	// mlx_loop(cub3d->mlx);
}
