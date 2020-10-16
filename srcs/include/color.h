/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:22:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/06 00:28:25 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int						create_trgb(int t, int r, int g, int b);
int						set_r(int trgb, int r);
int						set_g(int trgb, int g);
int						set_b(int trgb, int b);
int						get_r(int trgb);
int						get_g(int trgb);
int						get_b(int trgb);
int						add_shade(int trgb, double distance);

#endif
