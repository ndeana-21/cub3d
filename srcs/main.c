/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:52:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 16:33:33 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			print_lst(t_list *lst)//
{
	while (lst)
	{
		printf("|%s|\n", lst->content);
		lst = lst->next;
	}
}

int             main(int argc, char **argv)
{
	t_cub		*cub;

	if (!(cub = cub3d_init()) || 0 > arg_error(argc, argv, cub))
		return (0);
	if (0 > parser(cub))
		return (0);
	debug_print(cub);//
	// free_cub(cub);

    cub->win = mlx_new_window(
					cub->mlx, cub->res.x, cub->res.y, "cub3D");
	mlx_hook(cub->win, 2, 1L<<0, hook_press, cub);
	mlx_hook(cub->win, 3, 1L<<1, hook_release, cub);
	mlx_loop_hook(cub->mlx, render_next_frame, cub);
	mlx_loop(cub->mlx);
}

// img
// ==16217== 336 bytes in 21 blocks are indirectly lost in loss record 38 of 47
// ==16217==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==16217==    by 0x1147DC: ft_lstnew (ft_lstnew.c:19)
// ==16217==    by 0x10F347: file_reader (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110DCB: parser (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x10EB72: main (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)

// ==16217== 138 bytes in 10 blocks are indirectly lost in loss record 32 of 47
// ==16217==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==16217==    by 0x113ECE: ft_calloc (ft_calloc.c:19)
// ==16217==    by 0x114953: ft_substr (ft_substr.c:28)
// ==16217==    by 0x11430E: addline (ft_get_next_line.c:36)
// ==16217==    by 0x11464C: ft_get_next_line (ft_get_next_line.c:107)
// ==16217==    by 0x10F338: file_reader (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110DCB: parser (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x10EB72: main (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)

// ==16217== 120 (24 direct, 96 indirect) bytes in 1 blocks are definitely lost in loss record 27 of 47
// ==16217==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==16217==    by 0x10ED58: pathlst_append (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110B62: parse_path (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110CC9: parser_branch (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110E00: parser (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x10EB72: main (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)

// ==16217== 48 (24 direct, 24 indirect) bytes in 1 blocks are definitely lost in loss record 21 of 47
// ==16217==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==16217==    by 0x10ECCD: colorlst_append (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110A34: parse_color (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110CF8: parser_branch (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x110E00: parser (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
// ==16217==    by 0x10EB72: main (in /home/ndeana/21school/cub3d/cub3d_tr0/cub3D)
