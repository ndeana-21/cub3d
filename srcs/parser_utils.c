/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:32:59 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/14 18:11:38 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		window_valid(t_cub *cub)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(cub->mlx, &sizex, &sizey);
	if (cub->res.x > sizex)
		cub->res.x = sizex;
	if (cub->res.y > sizey)
		cub->res.y = sizey;
	return (1);
}

static int		player_init(t_map *map, int y, int x)
{
	if (ft_strchr("NSEW", map->map[y][x]))
	{
		if (!map->player)
		{
			if (!(map->player = malloc(sizeof(t_player))))
				return (print_error(""));
			map->player->pos.x = x + 0.5;
			map->player->pos.y = y + 0.5;
			if (map->map[y][x] == 'E')
				map->player->pow = 0.0;
			else if (map->map[y][x] == 'N')
				map->player->pow = 90.0;
			else if (map->map[y][x] == 'W')
				map->player->pow = 180.0;
			else
				map->player->pow = 270.0;
			return (1);
		}
		else
			return (print_error("MAP_ERROR too many player position"));
	}
	return (0);
}

static int		scan_around(t_map *map, int y, int x)
{
	if (ft_strchr(VALID_MAP, map->map[y][x]))
	{
		if (0 > (player_init(map, y, x)))
			return (-1);
		if (x == 0 || x == (map->res.x - 1) || y == 0 || y == (map->res.y - 1))
			return (ft_strchr(" 1", map->map[y][x]) ? 1 : -1);
		else
		{
			if (map->map[y][x] == ' ')
			{
				if (!(ft_strchr(" 1", map->map[y + 1][x])))
					return (-1);
				if (!(ft_strchr(" 1", map->map[y - 1][x])))
					return (-1);
				if (!(ft_strchr(" 1", map->map[y][x + 1])))
					return (-1);
				if (!(ft_strchr(" 1", map->map[y][x - 1])))
					return (-1);
			}
		}
		return (1);
	}
	return (-1);
}

static int		map_validator(t_map *map)
{
	int		x;	
	int		y;

	y = -1;
	while (++y < map->res.y)
	{
		x = 0;
		while (x < map->res.x)
		{
			if (0 > scan_around(map, y, x++))
				return (print_error("MAP_ERROR invalid map"));
		}
	}
	if (!map->player)
		return (print_error("MAP_ERROR have no player position"));
	return (2);
}

int				parse_map(t_map *map, t_list *page)
{
	t_list	*map_lst;
	int		max_x;
	
	max_x = 0;
	if (ft_strchr(page->content, '1') && ft_strsample(page->content, "1 "))
	{
		map_lst = ft_lstnew(page->content);
		page = page->next;
		while (page && ft_strchr(page->content, '1') &&
				ft_strsample(page->content, VALID_MAP))
		{
			max_x = ft_strlen(page->content);
			map->res.x = map->res.x < max_x ? max_x : map->res.x;
			ft_lstlast(map_lst)->next = ft_lstnew(page->content);
			page = page->next;
		}
		equal_map(map_lst, map->res.x);
		map->map = ft_lsttopage(map_lst, &(map->res.y));
		map->res.y = ft_lstsize(map_lst);
		ft_lstclear(&map_lst, free);
		if (!(map->map))
			return (print_error(""));
		return (map->res.y > 2 ? map_validator(map) : 0);
	}
	return (0);
}