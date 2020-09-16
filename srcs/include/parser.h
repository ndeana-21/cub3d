/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:53:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/14 18:10:40 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"

# define VALID_MAP " 012NSEW"
# define RES_SAMPLE "R "
# define COLOR_SAMPLE "F \0C \0\0"
# define WALL_IMG "NO \0SO \0WE \0EA \0\0"
# define SPRITE_ON_MAP "2"
# define SPRITE_IMG "S \0\0"
# define IMG_SAMPLE "NO \0SO \0WE \0EA \0S \0\0"

int		window_valid(t_cub *cub);
int		parse_map(t_map *map, t_list *page);

#endif