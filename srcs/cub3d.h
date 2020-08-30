/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:47:14 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/30 14:53:38 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

# define VALID_MAP " 012NSEW"
# define RES_SAMPLE "R "
# define COLOR_SAMPLE "F \0C \0"
# define TEXTURE_SAMPLE "NO \0SO \0WE \0EA \0S \0H \0"

typedef struct		s_data {
    void			*img;
    char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
}					t_data;

typedef struct		s_texture
{
	int				texture_count;
	char			**name_path;
	char			**texture_path;
	void			*img;
	int				trgb_count;
	char			**name_trgb;
	int				*trgb;
}					t_texture;

/**
 * pow = 0	 →
 * 		 90	 ↑
 * 		 180 ←
 * 		 270 ↓
**/

typedef struct		s_player
{
	int				exist;
	double			pow;
	double			x_pos;
	double			y_pos;
}					t_player;

typedef struct		s_map
{
	char			*map_path;
	int				map_x;
	int				map_y;
	char			**map;
	t_player		*player;
	t_texture		*texture;
}					t_map;

typedef struct		s_cub3d
{
	void			*mlx;
	void			*win;
	int				res_x;
	int				res_y;
	int				save;
	t_map			*map;
	t_data			*data;
}					t_cub3d;

t_cub3d				*cub3d_init();

int					create_trgb(int t, int r, int g, int b);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
int					add_shade(int trgb, double distance);
int					get_opposite(int trgb);

char				**ft_lsttodmas(t_list *list, int *y);
char				*ft_strpass(char *str, char *sample);
int					print_error(char *error);
int					arg_error(int argc, char **argv, t_cub3d *cub3d);
char				*find_sample(char *samples, char *str);

int					render_next_frame(t_cub3d *cub3d);
int					add_floor(t_cub3d *cub3d);
int					add_ceilling(t_cub3d *cub3d);

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);

int					hook_close(int keycode, t_cub3d *cub3d);
int					keycode_print(int keycode, t_cub3d *cub3d);


t_list				*file_reader(char *file);
int					equal_map(t_list *map, int x);
int					parse_map(t_map *map, t_list *page);
int					map_validator(t_map *map);

void 				debug_print(t_cub3d *cub3d);//
void				print_lst(t_list *lst);//

#endif
