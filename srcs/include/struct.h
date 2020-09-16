/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:28:54 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 01:33:30 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "cub3d.h"

typedef struct			s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct			s_res
{
	int					x;
	int					y;
}						t_res;

typedef struct			s_vec
{
	t_point				start;
	t_point				end;
}						t_vec;

typedef struct			s_img
{
	void				*img;
	int					x;
	int					y;
}						t_img;

typedef struct			s_colorlst
{
	char				*name;
	int					trgb;
	struct t_colorlst	*next;
}						t_colorlst;

typedef struct			s_pathlst
{
	char				*name;
	t_img				*img;
	struct t_pathlst	*next;
}						t_pathlst;


typedef struct			s_ray
{
	t_vec				vec;
	double				pow;
	char				wall;
	struct t_ray		*next_ray;
}						t_ray;

typedef struct			s_data
{
    void				*img;
    char				*addr;
    int					bits_per_pixel;
    int					line_length;
    int					endian;
}						t_data;

typedef struct			s_parsed
{
	t_pathlst			*path;
	t_colorlst			*color;
}						t_parsed;

/**
 * pow = 0	 →
 * 		 90	 ↑
 * 		 180 ←
 * 		 270 ↓
**/
typedef struct			s_player
{
	int					exist;
	double				pow;
	t_point				pos;
}						t_player;

typedef struct			s_wall
{
	t_vec				vec;
	struct t_wall		*next_wall;
}						t_wall;

typedef struct			s_walls
{
	t_wall				*south;
	t_wall				*east;
	t_wall				*west;
	t_wall				*north;
	void				*img_south;
	void				*img_east;
	void				*img_west;
	void				*img_north;
}						t_walls;

typedef struct			s_sprites
{
	t_img				*img;
	t_point				coord;
	struct t_sprites	*next_sprite;
}						t_sprites;

typedef struct			s_map
{
	char				*map_path;
	t_res				res;
	char				**map;
	t_ray				*ray;
	double				ray_pow_step;
	t_walls				*walls;
	t_sprites			*sprites;
	t_player			*player;
	t_parsed			*img;
}						t_map;

typedef struct			s_key
{
	char				w;
	char				s;
	char				a;
	char				d;
	char				q;
	char				e;
}						t_key;

typedef struct			s_cub
{
	void				*mlx;
	void				*win;
	t_data				*data;
	int					save;
	t_res				res;
	t_key				keys;
	t_map				*map;
}						t_cub;

#endif