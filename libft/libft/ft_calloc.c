/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:41:21 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 12:47:30 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*cal;

	if (nmemb == 0 || size == 0)
		return ((void *)0);
	if ((nmemb * size) / nmemb != size)
		return ((void *)0);
	cal = malloc(nmemb * size);
	if (cal)
		ft_bzero(cal, nmemb * size);
	return (cal);
}
