/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:23:04 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/13 17:43:25 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstclear(t_list *lst, void (*del)(void*))
{
	t_list	*tlst;

	tlst = lst;
	if (!lst)
		return (lst);
	if (del)
		while (lst)
		{
			tlst = lst->next;
			lst = ft_lstdelone(lst, del);
			lst = tlst;
		}
	return (NULL);
}
