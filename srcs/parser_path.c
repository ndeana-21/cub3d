/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 00:38:36 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/14 23:18:09 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pathlst		*pathlst_last_element(t_pathlst *lst)
{
	t_pathlst	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = (t_pathlst *)tmp->next;
	return (tmp);
}

void			pathlst_append(t_cub *cub, char *sample, char *path)
{
	t_pathlst	*tmp;
	t_pathlst	*new;

	if (!(new = malloc(sizeof(t_pathlst))))
		print_error(cub, "ERROR malloc");
	*new = (t_pathlst){sample, path, img_init(cub), NULL};
	if (!(new->img->data->img = mlx_xpm_file_to_image(cub->mlx, path,
	&new->img->x, &new->img->y)))
		print_error(cub, "MLX_ERROR xpm img");
	if (!(new->img->data->addr = mlx_get_data_addr(new->img->data->img,
	&new->img->data->bpp, &new->img->data->line_len, &new->img->data->endian)))
		print_error(cub, "MLX_ERROR xpm img");
	tmp = NULL;
	if (!(tmp = pathlst_last_element(cub->map->img->path)))
	{
		cub->map->img->path = new;
		return ;
	}
	tmp->next = (struct t_pathlst *)new;
}

int				path_reptcheck(t_pathlst *path, char *sample)
{
	t_pathlst *tmp;

	if (!path)
		return (FALSE);
	tmp = path;
	while (tmp)
	{
		if ((int)ft_strlen(sample) == ft_strcmp(tmp->name, sample))
			return (TRUE);
		tmp = (t_pathlst *)tmp->next;
	}
	return (FALSE);
}
