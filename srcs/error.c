/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:16:09 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/14 18:12:30 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				print_error(char *error)
{
	if (!error)
		perror(error);
	else
		ft_putendl_fd(error, 2);
	return (-1);
}

int			arg_error(int argc, char **argv, t_cub *cub)
{
	int		len;

	if (argc < 2)
		return (print_error("ERROR too few args"));
	else if (argc > 3)
		return (print_error("ERROR too many args"));
	else if (argc == 3)
	{
		if (!(ft_strncmp(argv[2], "--save", 7)))
			cub->save = 1;
		else
			return (print_error("ERROR unknown arg"));
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || '.' != argv[1][len - 4] ||
			'b' != (ft_strncmp(&argv[1][len - 4], ".cub", 4)))
		return (print_error("ERROR filename doesn't end with the `.cub`"));
	if (!(cub->map->map_path = ft_strdup(argv[1])))
		return (print_error("allocation ERROR"));
	return (1);
}

void 		debug_print(t_cub *cub)//
{
	int	i = 0;
	printf("\n\n-------------DEBUG--------------\n");
	printf("====cub====\n");
	printf("res x:%d y:%d\nsave:%d\n", cub->res.x, cub->res.y, cub->save);
	printf("=====map=====\n");
	printf("map_path: %s\nmap x:%d y:%d\n==============map_start===========\n",
			cub->map->map_path, cub->map->res.x, cub->map->res.y);
	int y = 0;
	while (y < cub->map->res.y)
	{
		printf("|%s|\n", cub->map->map[y]);
		y++;
	}
	printf("===============map_end============\n");
	if (cub->map->player)
	{
		printf("====player====\n");
		printf("pow = %lf\nplayer x:%lf y:%lf\n",
				cub->map->player->pow,
				cub->map->player->pos.x, cub->map->player->pos.y);
	}
	printf("====img=======\n");
	t_pathlst *path = cub->map->img->path;
	while (path)
	{
		printf("-------------\nsample - %s\n",
			path->name);
		path = path->next;
	}
	printf("====colors====\n");
	t_colorlst *color = cub->map->img->color;
	while (color)
	{
		printf("-------------\nsample - %s\ntrgb   - %d\n",
			color->name,
			color->trgb);
		color = color->next;
	}
}
