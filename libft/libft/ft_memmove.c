/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:29:53 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 12:52:25 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;

	tmpdest = (unsigned char *)dest;
	tmpsrc = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	if (tmpdest < tmpsrc)
		while (n--)
			*tmpdest++ = *tmpsrc++;
	else
		while (--n + 1)
			tmpdest[n] = tmpsrc[n];
	return (dest);
}
