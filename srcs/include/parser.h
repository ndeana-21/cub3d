/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:53:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 22:43:38 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "struct.h"
# include "color.h"
# include "mlx.h"
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# define VALID_MAP " 012NSEW"
# define INSIDE_MAP "02NSEW"
# define INSIDE_AND_WALL_MAP "102NSEW"
# define RES_SAMPLE "R "
# define COLOR_SAMPLE "F \0C \0\0"
# define WALL_IMG "NO \0SO \0WE \0EA \0\0"
# define SPRITE_ON_MAP "2"
# define SPRITE_IMG "S \0\0"
# define IMG_SAMPLE "NO \0SO \0WE \0EA \0S \0\0"

void		window_valid(t_cub *cub);
int			parse_map(t_cub *cub, t_map *map, t_list *page);
t_list		*file_reader(t_cub *cub, char *file);
char		*ft_findsample(t_cub *cub, char *samples, char *str);
char		*ft_strpass(char *str, char *sample);
int			color_reptcheck(t_colorlst *color, char *sample);
int			path_reptcheck(t_pathlst *path, char *sample);
void		pathlst_append(t_cub *cub3d, char *sample, char *path);
t_colorlst	*colorlst_append(t_colorlst *lst, char *sample, int trgb);
int			print_error(t_cub *cub, char *error);
char		*check_sample(char *sample, char *str);
t_img		*img_init(t_cub *cub);
int			valid_color(t_cub *cub, char *str);

#endif
