/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:28:54 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/09 18:22:53 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct			s_data
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_data;

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
	t_data				*data;
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
	char				*path;
	t_img				*img;
	struct t_pathlst	*next;
}						t_pathlst;

typedef struct			s_ray
{
	t_vec				vec;
	double				pow;
	char				wall;
	double				dst;
}						t_ray;

typedef struct			s_parsed
{
	t_pathlst			*path;
	t_colorlst			*color;
}						t_parsed;

typedef struct			s_player
{
	double				pow;
	t_point				pos;
	double				pow_y;
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
	t_img				*img_s;
	t_img				*img_e;
	t_img				*img_w;
	t_img				*img_n;
	int					celling;
	int					floor;
}						t_walls;

typedef struct			s_sprite
{
	t_point				coord;
	double				pow;
	int					start_pnt;
	int					wide;
	int					hight;
	double				dst;
}						t_sprite;

typedef struct			s_sprites
{
	t_img				*img;
	t_sprite			*spr;
}						t_sprites;

typedef struct			s_map
{
	t_res				res;
	double				ray_pow_step;
	char				*map_path;
	char				**map;
	t_ray				*ray;
	t_walls				*walls;
	t_sprites			*sprite;
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
	char				m;
	char				h;
	char				up;
	char				down;
	char				left;
	char				right;
	char				shift;
	int					mouse_x;
	int					mouse_y;
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
