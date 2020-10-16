/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:16:09 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 23:11:04 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			print_error(t_cub *cub, char *error)
{
	ft_putendl_fd(error, 2);
	cub = NULL;
	exit(-1);
	return (-1);
}

int			arg_error(int argc, char **argv, t_cub *cub)
{
	int		len;

	if (argc < 2)
		print_error(cub, "ERROR too few args");
	else if (argc > 3)
		print_error(cub, "ERROR too many args");
	else if (argc == 3)
	{
		if (!(ft_strncmp(argv[2], "--save", 7)))
			cub->save = 1;
		else
			print_error(cub, "ERROR unknown arg");
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || '.' != argv[1][len - 4] ||
			'b' != (ft_strncmp(&argv[1][len - 4], ".cub", 4)))
		print_error(cub, "ERROR filename doesn't end with the `.cub`");
	if (!(cub->map->map_path = ft_strdup(argv[1])))
		print_error(cub, "allocation ERROR");
	return (1);
}

int			close_window(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	cub->win = NULL;
	exit(0);
}
