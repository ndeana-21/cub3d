/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:53:52 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/30 04:18:49 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				window_valid(t_cub3d *cub3d)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(cub3d->mlx, &sizex, &sizey);
	if (cub3d->res_x > sizex)
		cub3d->res_x = sizex;
	if (cub3d->res_y > sizey)
		cub3d->res_y = sizey;
	return (1);
}

static int		parse_color(t_texture *texture, char *str)
{
	int		r;
	int		g;
	int		b;

	str = ft_strpass(str, " ");
	if (!(texture->name_trgb = find_sample(COLOR_SAMPLE, str)))
		return (0);
	str = ft_strpass(str, "CF");
	str = ft_strpass(str, " ");
	r = ft_atoi(str);
	str = ft_strpass(str, "0123456789 ");
	str = ft_strpass(str, ",");
	g = ft_atoi(str);
	str = ft_strpass(str, "0123456789 ");
	str = ft_strpass(str, ",");
	b = ft_atoi(str);
	texture->trgb = create_trgb(0, r, g, b);
	return (1);
}

static int		parse_path(t_texture *texture, char *str)
{
	char	*sample;
	int		fd;

	if (!(sample = find_sample(TEXTURE_SAMPLE, str)))
		return (0);
	texture->texture_count++;
	if (!(texture->name_path = (char **) ft_realloc(texture->name_path,
								sizeof(char *) * texture->texture_count)))
		return (print_error("alloc ERROR\n"));
	texture->texture_path[texture->texture_count - 1] = ft_strtrim(str, " ");
	free(sample);
	if (0 > (fd = open(texture->texture_path, O_RDONLY)))
	{
		texture->texture_path[--texture->texture_count] = NULL;
		return (print_error("ERROR can not open picture\n"));
	}
	close(fd);
	return (1);
}

static int		parse_res(t_cub3d *cub3d, char *str)
{
	str = ft_strpass(str, " ");
	if (str = ft_strchr(RES_SAMPLE, str))
		return (0);
	
}

int				parser(t_cub3d *cub3d, t_list *lst)
{
	int		ret;

	ret = 0;
	while(lst)
	{
		if (ret = parse_res(cub3d, lst->content))
			if (ret > 0)
				return (ret);
		else if (ret = parse_path(cub3d->map->texture, lst->content))
			if (ret > 0)
				return (ret);
		else if (ret = parse_color(cub3d->map->texture, lst->content))
			if (ret > 0)
				return(ret);
		else if (ret = parse_map(cub3d->map, lst))
			if (ret > 0)
				return(ret);
		lst = lst->next;
	}
}

static int		player_init(t_map *map, int y, int x)
{
	if (ft_strchr("NSEW", map->map[y][x]))
	{
		if (!(map->player->exist))
		{
			map->player->exist = 1;
			map->player->x_pos = x;
			map->player->y_pos = y;
			if (map->map[x][y] == 'E')
				map->player->pow = 0.0;
			else if (map->map[x][y] == 'N')
				map->player->pow = 90.0;
			else if (map->map[x][y] == 'W')
				map->player->pow = 180.0;
			else
				map->player->pow = 270.0;
			return (1);
		}
		else
			return (print_error("MAP_ERROR too many player position\n"));
	}
	return (1);
}

static int		scan_around(t_map *map, int y, int x)
{
	if (ft_strchr(VALID_MAP, map->map[y][x]))
	{
		if (0 > (player_init(map, y, x)))
			return (-1);
		if (x == 0 || x == (map->map_x - 1) || y == 0 || y == (map->map_y - 1))
			return ((map->map[y][x] == ' ' || map->map[y][x] == '1') ? 1 : -1);
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
	else
		return (-1);
}

int				map_validator(t_map *map)
{
	int		x;	
	int		y;

	y = 0;
	x = 0;
	while (y < map->map_y)
	{
		while (x < map->map_x)
		{
			if (0 > scan_around(map, y, x))
				return (print_error("MAP_ERROR invalid map\n") + 1);
			x++;
		}
		x = 0;
		y++;
	}
	if (!map->player->exist)
		return (print_error("MAP_ERROR have no player position\n") + 1);
	return (1);
}

int				parse_map(t_map *map, t_list *page)
{
	t_list	*map_lst;
	int		max_x;
	
	max_x = 0;
	if (ft_strsample(page->content, "1 ") && !(map->map))
	{
		map_lst = ft_lstnew(page->content);
		page = page->next;
		while (page->content && ft_strsample(page->content, VALID_MAP))
		{
			max_x = ft_strlen(page->content);
			map->map_x = map->map_x < max_x ? max_x : map->map_x;
			ft_lstlast(map_lst)->next = ft_lstnew(page->content);
			page = page->next;
		}
		equal_map(map_lst, map->map_x);
		map->map = ft_lsttodmas(map_lst, &map->map_y);
		ft_lstclear(&map_lst, free);
		if (!(map->map))
			return (print_error("alloc ERROR\n"));
		return (map->map_y > 2 ? map->map_y : 0);
	}
	return (0);
}
