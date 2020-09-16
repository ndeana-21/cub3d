/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:47:14 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 16:38:48 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include "color.h"
# include "struct.h"
# include <math.h>
# include <stdio.h>//
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# define PI 3.14159265
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define MV_SPEED 0.05
# define TR_SPEED 0.05
# define PLAYER_FOW 70
# define SPRITE_SAMPLE "S "
# define SPRITES "2"
# define COLISION "1 "
# define NO_VISION "02NSEW"

t_cub		*cub3d_init();
void		free_cub(t_cub *cub);
void		*free_wall(t_wall *wall);
void		*free_sprites(t_sprites *sprites);


int			render_next_frame(t_cub *cub);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

int			colision(t_map *map, t_point pos);
double		pow_turn(double pow, double turn);
int			player_move(t_map *map, t_player *player, double pow);
int			player_keys_move(t_cub *cub);

int			hook_close(int keycode, t_cub *cub);
int			hook_press(int keycode, t_cub *cub);
int			hook_release(int keycode, t_cub *cub);
int			keycode_print(int keycode, t_cub *cub);

t_list		*file_reader(char *file);//replace
int			equal_map(t_list *map, int x);//replace
int			parser(t_cub *cub);

int			ll_intersect(t_vec *ray, t_vec wall);
t_vec		ray_cast(t_wall *wall, t_point pos, t_res max, double pow);
t_ray		*ray_init(int count_rays);

/**
 * 					UTILITY
**/

void		paint_circle(t_cub *cub, int trgb, t_point coord, int scale);
void		paint_square(t_cub *cub, int trgb, t_point coord, int scale);
void		paint_line(t_cub *cub, int trgb, t_vec vec);
void		paint_rectangle(t_cub *cub, int trgb, t_res start, t_res end);

t_vec		make_vector(double x1, double y1, double x2, double y2);
t_point		make_point(double x, double y);
double		equal_range(double x, double y);

char		*check_sample(char *sample, char *str);
char		**ft_lsttopage(t_list *list, int *y);
char		*ft_strpass(char *str, char *sample);
int			print_error(char *error);
int			arg_error(int argc, char **argv, t_cub *cub);
char		*ft_findsample(char *samples, char *str);
t_img		*find_img(t_pathlst *path, char *str);
double		deg(double rad);
double		rad(double deg);

void 		debug_print(t_cub *cub);//delete
void		print_lst(t_list *lst);//delete
t_colorlst	*colorlst_append(t_colorlst *lst,char *sample, int trgb);
int			pathlst_append(t_cub *cub, char *sample, char *path);
int			color_reptcheck(t_colorlst *color, char *sample);
int			path_reptcheck(t_pathlst *path, char *sample);

#endif
