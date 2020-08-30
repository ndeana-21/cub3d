/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:35:06 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/29 02:27:37 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dub;
	size_t	i;

	if (!(dub = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		dub[i] = s[i];
		i++;
	}
	dub[i] = '\0';
	return (dub);
}
