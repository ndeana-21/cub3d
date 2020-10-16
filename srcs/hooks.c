/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 22:14:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/07 02:05:15 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keys_linux.h"

int	hook_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	if (keycode == KEY_M)
		cub->keys.m = cub->keys.m ? FALSE : TRUE;
	if (keycode == KEY_H)
		cub->keys.h = cub->keys.h ? FALSE : TRUE;
	cub->keys.w = keycode == KEY_W ? TRUE : cub->keys.w;
	cub->keys.a = keycode == KEY_A ? TRUE : cub->keys.a;
	cub->keys.s = keycode == KEY_S ? TRUE : cub->keys.s;
	cub->keys.d = keycode == KEY_D ? TRUE : cub->keys.d;
	cub->keys.up = keycode == KEY_UP ? TRUE : cub->keys.up;
	cub->keys.down = keycode == KEY_DOWN ? TRUE : cub->keys.down;
	cub->keys.left = keycode == KEY_LEFT ? TRUE : cub->keys.left;
	cub->keys.right = keycode == KEY_RIGHT ? TRUE : cub->keys.right;
	cub->keys.shift = keycode == KEY_SHIFT ? TRUE : cub->keys.shift;
	return (TRUE);
}

int	hook_release(int keycode, t_cub *cub)
{
	cub->keys.w = keycode == KEY_W ? FALSE : cub->keys.w;
	cub->keys.a = keycode == KEY_A ? FALSE : cub->keys.a;
	cub->keys.s = keycode == KEY_S ? FALSE : cub->keys.s;
	cub->keys.d = keycode == KEY_D ? FALSE : cub->keys.d;
	cub->keys.up = keycode == KEY_UP ? FALSE : cub->keys.up;
	cub->keys.down = keycode == KEY_DOWN ? FALSE : cub->keys.down;
	cub->keys.left = keycode == KEY_LEFT ? FALSE : cub->keys.left;
	cub->keys.right = keycode == KEY_RIGHT ? FALSE : cub->keys.right;
	cub->keys.shift = keycode == KEY_SHIFT ? FALSE : cub->keys.shift;
	return (FALSE);
}

int	hook_mouse_x(int mouse_x, int mouse_y, t_cub *cub)
{
	cub->keys.mouse_x = mouse_x - (cub->res.x / 2);
	cub->keys.mouse_y = mouse_y - (cub->res.y / 2);
	return (0);
}
