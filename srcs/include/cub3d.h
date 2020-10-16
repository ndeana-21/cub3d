/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:47:14 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 15:13:24 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include "bitmapfile.h"
# include "color.h"
# include "struct.h"
# include <math.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# define MV_SPEED 0.04
# define TR_SPEED 1.0
# define PLAYER_FOW 60
# define BLANK_SPRITE -6815608
# define FLOOR_SAMPLE "F "
# define SPRITE_SAMPLE "S "
# define CELLING_SAMPLE "C "
# define SPRITES '2'
# define COLISION ""
# define NO_VISION "02NSEW"

t_cub		*cub3d_init(void);
void		raw_to_obj_walls(t_cub *cub, t_map *map);
void		raw_to_obj_sprite(t_cub *cub, t_map *map, char sample);

int			render_frame(t_cub *cub);
int			render_next_frame(t_cub *cub);
void		minimap(t_map *map, t_cub *cub);
void		render_cf(t_ray ray, t_cub *cub, t_res point);
void		render_wall(t_ray ray, t_cub *cub, t_res xy, t_walls wl);
void		render_sprite(t_ray *ray, t_cub *cub, t_sprites *sprites);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			my_mlx_pixel_get(t_data *data, int x, int y);
int			get_pix_wall(t_img *img, t_ray ray, double ratio_y);
void		sort_sprite(t_sprite *spr, t_point point);
int			get_spr_win_pos(t_player player, t_cub *cub, t_sprite spr);
void		paint_sprite(t_ray *ray, t_cub *cub, t_sprite spr, t_img *img);
double		anti_fisheye(double player, double ray);

int			colision(t_map *map, t_vec *pos);
int			player_move(t_map *map, t_player *player, double pow);
int			player_keys_move(t_cub *cub);
double		pow_turn(double pow, double turn, double min, double max);
double		pow_turn_updown(double pow, double turn);
int			player_cam_y(int res_y, double player_pow_y);

int			close_window(t_cub *cub);
int			close_window_cross(t_cub *cub);
int			hook_press(int keycode, t_cub *cub);
int			hook_release(int keycode, t_cub *cub);
int			hook_mouse_x(int mouse_x, int mouse_y, t_cub *cub);

int			ll_intersect(t_vec *ray, t_vec wall);
void		ray_init(t_cub *cub, t_map *map);
int			ray_cast(t_vec *ray, t_wall *wall);
void		rays_casting(t_ray *rays, t_cub *cub, t_map *map, int count_rays);

t_img		*img_init(t_cub *cub);
t_img		*find_img(t_pathlst *path, char *str);
int			count_sprites(t_map *map, char sample);
void		find_color_cf(t_cub *cub, t_walls *walls, t_colorlst *color);

void		paint_line(t_cub *cub, int trgb, t_vec vec);
void		paint_circle(t_cub *cub, int trgb, t_point coord, int scale);
void		paint_square(t_cub *cub, int trgb, t_point coord, int scale);
void		paint_rectangle(t_cub *cub, int trgb, t_res start, t_res end);

t_vec		make_vector(double x1, double y1, double x2, double y2);
double		equal_dst(t_point player, t_point pos);

char		*check_sample(char *sample, char *str);
double		ft_mod(double num);
double		ft_deg_of_vec(t_point from, t_point to, double dst);

void		save_bmp(t_cub *cub);

int			print_error(t_cub *cub, char *error);
int			arg_error(int argc, char **argv, t_cub *cub);

int			parser(t_cub *cub);

#endif
