/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:56:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:00:48 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0 && (!src || !dest))
		return (0);
	if (ft_strlen(dest) +1 > size)
		return (ft_strlen(src) + size);
	while (dest[j])
		j++;
	while (j +1 < size && src[i])
		dest[j++] = src[i++];
	if (size == 0 || !src[i] || j + 1 == size)
		dest[j] = '\0';
	return (ft_strlen(dest) + ft_strlen(src) - i);
}
