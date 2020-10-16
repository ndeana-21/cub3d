/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 00:40:18 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 22:43:51 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		player_init(t_cub *cub, t_map *map, int y, int x)
{
	if (ft_strchr("NSEW", map->map[y][x]))
	{
		if (!map->player)
		{
			if (!(map->player = malloc(sizeof(t_player))))
				print_error(cub, "ERROR malloc");
			map->player->pos.x = x + 0.5;
			map->player->pos.y = y + 0.5;
			map->player->pow_y = 90.0;
			if (map->map[y][x] == 'N')
				map->player->pow = 180.0;
			else if (map->map[y][x] == 'W')
				map->player->pow = 270.0;
			else if (map->map[y][x] == 'S')
				map->player->pow = 0.0;
			else if (map->map[y][x] == 'E')
				map->player->pow = 90.0;
			return (TRUE);
		}
		else
			print_error(cub, "MAP_ERROR too many player position");
	}
	return (FALSE);
}

static int		scan_around(t_cub *cub, t_map *map, int y, int x)
{
	if (ft_strchr(VALID_MAP, map->map[y][x]))
	{
		if (0 > (player_init(cub, map, y, x)))
			return (ERROR);
		if (x == 0 || x == (map->res.x - 1) || y == 0 || y == (map->res.y - 1))
			return (ft_strchr(" 1", map->map[y][x]) ? 1 : -1);
		else
		{
			if (ft_strchr(INSIDE_MAP, map->map[y][x]))
				if (!(ft_strchr(INSIDE_AND_WALL_MAP, map->map[y + 1][x])) ||
					!(ft_strchr(INSIDE_AND_WALL_MAP, map->map[y - 1][x])) ||
					!(ft_strchr(INSIDE_AND_WALL_MAP, map->map[y][x + 1])) ||
					!(ft_strchr(INSIDE_AND_WALL_MAP, map->map[y][x - 1])))
					return (ERROR);
		}
		return (TRUE);
	}
	return (ERROR);
}

static int		map_validator(t_cub *cub, t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->res.y)
	{
		x = -1;
		while (++x < map->res.x)
		{
			if (0 > scan_around(cub, map, y, x))
				print_error(cub, "MAP_ERROR invalid map");
		}
	}
	if (!map->player)
		print_error(cub, "MAP_ERROR have no player position");
	return (2);
}

static void		equal_map(t_cub *cub, t_list *map, int x)
{
	int		i;
	int		j;
	char	*buf;

	if (!(map))
		print_error(cub, "ERROR empty map\n");
	while (TRUE)
	{
		if ((i = ft_strlen(map->content)) < x)
		{
			if (!(buf = (char *)malloc(sizeof(char) * x + 1)))
				print_error(cub, "allocation ERROR");
			j = -1;
			while (((char *)(map->content))[++j])
				buf[j] = ((char *)(map->content))[j];
			while (j < x)
				buf[j++] = ' ';
			buf[j] = '\0';
			free(map->content);
			map->content = buf;
		}
		if (!(map = (t_list *)map->next))
			break ;
	}
}

int				parse_map(t_cub *cub, t_map *map, t_list *page)
{
	t_list	*map_lst;
	int		max_x;

	max_x = 0;
	if (ft_strchr(page->content, '1') && ft_strsample(page->content, "1 "))
	{
		map_lst = ft_lstnew(ft_strdup(page->content));
		page = page->next;
		while (page && ft_strchr(page->content, '1') &&
				ft_strsample(page->content, VALID_MAP))
		{
			max_x = ft_strlen(page->content);
			map->res.x = map->res.x < max_x ? max_x : map->res.x;
			ft_lstlast(map_lst)->next = ft_lstnew(ft_strdup(page->content));
			page = page->next;
		}
		equal_map(cub, map_lst, map->res.x);
		map->map = ft_lsttopage(map_lst, &(map->res.y));
		map->res.y = ft_lstsize(map_lst);
		map_lst = ft_lstclear(map_lst, free);
		if (!(map->map))
			print_error(cub, "ERROR malloc");
		return (map_validator(cub, map));
	}
	return (FALSE);
}
