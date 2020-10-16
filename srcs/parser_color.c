/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 00:38:51 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 23:08:57 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_colorlst		*colorlst_append(t_colorlst *lst, char *sample, int trgb)
{
	t_colorlst *tmp;
	t_colorlst *new;

	if (!lst->name)
	{
		*lst = (t_colorlst){sample, trgb, NULL};
		return (lst);
	}
	if (!(new = malloc(sizeof(t_colorlst))))
		return (NULL);
	*new = (t_colorlst){sample, trgb, NULL};
	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = (t_colorlst *)tmp->next;
	tmp->next = (struct t_colorlst *)new;
	return (lst);
}

int				color_reptcheck(t_colorlst *color, char *sample)
{
	t_colorlst *tmp;

	if (!color)
		return (0);
	tmp = color;
	while (tmp)
	{
		if (tmp->name)
			if ((int)ft_strlen(sample) == ft_strcmp(tmp->name, sample))
				return (TRUE);
		tmp = (t_colorlst *)tmp->next;
	}
	return (FALSE);
}

int				valid_color(t_cub *cub, char *str)
{
	int	trgb;
	int	color;

	if (0 > (color = ft_atoi(str)) || color > 255)
		print_error(cub, "CUB_ERROR color have to be 0 - 255");
	trgb = set_r(0, color);
	str = ft_strpass(ft_strpass(str, "0123456789"), " ");
	if (!ft_isdigit(*(str = ft_strpass(*str == ',' ? str + 1 : str, " "))))
		print_error(cub, "CUB_ERROR invalid color");
	if (0 > (color = ft_atoi(str)) || color > 255)
		print_error(cub, "CUB_ERROR color have to be 0 - 255");
	trgb = set_g(trgb, color);
	str = ft_strpass(ft_strpass(str, "0123456789"), " ");
	if (!ft_isdigit(*(str = ft_strpass(*str == ',' ? str + 1 : str, " "))))
		print_error(cub, "CUB_ERROR invalid color");
	if (0 > (color = ft_atoi(str)) || color > 255)
		print_error(cub, "CUB_ERROR color have to be 0 - 255");
	trgb = set_b(trgb, color);
	if (*(str = ft_strpass(ft_strpass(str, "0123456789"), " ")))
		print_error(cub, "CUB_ERROR invalid color");
	return (trgb);
}
