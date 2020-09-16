/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 22:14:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/15 03:58:28 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keys_linux.h"

int	hook_press(int keycode, t_cub *cub3d)
{
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(cub3d->mlx, cub3d->win);
		exit(0);
	}
	if (keycode == KEY_W)
		cub3d->keys.w = 1;
	if (keycode == KEY_A)
		cub3d->keys.a = 1;
	if (keycode == KEY_S)
		cub3d->keys.s = 1;
	if (keycode == KEY_D)
		cub3d->keys.d = 1;
	if (keycode == KEY_Q)
		cub3d->keys.q = 1;
	if (keycode == KEY_E)
		cub3d->keys.e = 1;
	return (0);
}

int	hook_release(int keycode, t_cub *cub3d)
{
	if (keycode == KEY_W)
		cub3d->keys.w = 0;
	if (keycode == KEY_A)
		cub3d->keys.a = 0;
	if (keycode == KEY_S)
		cub3d->keys.s = 0;
	if (keycode == KEY_D)
		cub3d->keys.d = 0;
	if (keycode == KEY_Q)
		cub3d->keys.q = 0;
	if (keycode == KEY_E)
		cub3d->keys.e = 0;
	return (0);
}

int	keycode_print(int keycode, t_cub *cub3d)
{
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
}

int	hook_mouse(int keycode, t_cub *cub3d)
{
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
