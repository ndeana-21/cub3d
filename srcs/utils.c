/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:10:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 16:39:20 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//
t_colorlst *colorlst_append(t_colorlst *lst,char *sample, int trgb)
{
	t_colorlst *tmp;
	t_colorlst *new;


	if (!(new = malloc(sizeof(t_colorlst))))
		return (NULL);
	new->name = sample;
	new->trgb = trgb;
	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}
//
int					pathlst_append(t_cub *cub3d, char *sample, char *path)
{
	t_pathlst	*tmp;
	t_pathlst	*new;
	t_img		*img;

	if (!(new = malloc(sizeof(t_pathlst))) ||
		!(img = malloc(sizeof(t_img))))
		return (print_error(""));
	new->name = sample;
	if (!(img = mlx_xpm_file_to_image(cub3d->mlx, path,
										&img->x, &img->y)))
		return (print_error("MLX_ERROR xpm img"));
	free(path);
	if (!cub3d->map->img->path)
	{
		cub3d->map->img->path = new;
		return (1);
	}
	tmp = cub3d->map->img->path;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
//
int				path_reptcheck(t_pathlst *path, char *sample)
{
	t_pathlst *tmp;

	if (!path)
		return (0);
	tmp = path;
	while (tmp)
	{
		if (ft_strlen(sample) == ft_strcmp(tmp->name, sample))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
//
int				color_reptcheck(t_colorlst *color, char *sample)
{
	t_colorlst *tmp;

	if (!color)
		return (0);
	tmp = color;
	while (tmp)
	{
		if (ft_strlen(sample) == ft_strcmp(tmp->name, sample))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char			*check_sample(char *sample, char *str)
{
	while (*sample && *str)
	{
		if (*sample != *str)
			return (0);
		str++;
		sample++;
	}
	return (str);
}

char		**ft_lsttopage(t_list *lst, int *y)
{
	int		i;
	char	**dmas;

	if (!lst)
		return (NULL);
	*y = ft_lstsize(lst);
	if (!(dmas = (char **)malloc(ft_lstsize(lst) * sizeof(size_t))))
		return (NULL);
	i = 0;
	while (i < *y)
	{
		if (!(dmas[i++] = ft_strdup(lst->content)))
			return (NULL);
		lst = lst->next;
	}
	return (dmas);
}

char			*ft_strpass(char *str, char *sample)
{
	while (*str)
	{
		if (ft_strchr(sample, *str))
			str++;
		else
			return(str);
	}
	return (str);
}

char			*ft_findsample(char *samples, char *str)
{
	char	*sample_out;
	int		i;
	int		j;

	i = 0;
	while (samples[i])
	{
		j = 0;
		while (samples[i + j] && str[j])
			if (samples[i + j] != str[j++])
				break;
		if (!samples[i + j])
		{
			if (!(sample_out = ft_strdup(&samples[i])))
				return (NULL);
			return (sample_out);
		}
		else
			while (samples[i + j])
				j++;
		i += j + 1;
	}
	return (NULL);
}
//
int			equal_map(t_list *map, int x)
{
	int		i;
	char	*tmp;

	if (!(map))
		return (print_error("ERROR equal_map - empty map\n"));
	while (1)
	{
		i = ft_strlen(map->content);
		if (i < x)
		{
			if (!(map->content = (char *)ft_realloc(map->content, sizeof(char) * x + 1)))
				return (print_error("allocation ERROR\n"));
			while (i < x)
				((char *)map->content)[i++] = ' ';
			((char *)map->content)[i] = 0;
		}
		map = map->next;
		if (!map)
			break ;
	}
	return (1);
}

t_list			*file_reader(char *file)
{
	t_list	*start_lst;
	t_list	*lst;
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	if (0 > (fd = open(file, O_RDONLY)))
		return (NULL);
	ret = ft_get_next_line(fd, &line);
	if (!(start_lst = ft_lstnew(line)))
		return (NULL);
	lst = start_lst;
	while (0 < ret)
	{
		ret = ft_get_next_line(fd, &line);
		if (!(lst->next = ft_lstnew(line)))
			return (NULL);
		lst = lst->next;
	}
	close(fd);
	if (ret < 0)
		return (NULL);
	return (start_lst);
}

double			rad(double deg)
{
	return (deg * PI / 180);
}

double			deg(double rad)
{
	return (rad * 180 / PI);
}

t_vec			make_vector(double x1, double y1, double x2, double y2)
{
	t_vec	vec;

	vec.start.x = x1;
	vec.start.y = y1;
	vec.end.x = x2;
	vec.end.y = y2;
	return (vec);
}

t_point			make_point(double x, double y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

double			equal_range(double x, double y)
{
	return (sqrt(pow(x, 2) + pow(y, 2)));
}

t_img			*find_img(t_pathlst *path, char *str)
{
	t_pathlst	*path_current;

	path_current = path;
	while (path_current)
	{
		if (ft_strlen(SPRITE_SAMPLE) ==
			ft_strcmp(SPRITE_SAMPLE, path_current->name))
			return (path_current->img);
		path_current = path_current->next;
	}
	return (NULL);
}
