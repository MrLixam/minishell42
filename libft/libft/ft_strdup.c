/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:18:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:00:08 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strdup(const char *src)
{
	char	*tmp;
	char	*dest;
	size_t	i;

	i = 0;
	tmp = (char *)src;
	dest = malloc(ft_strlen(tmp)+1);
	if (!dest)
		return (dest);
	while (i < ft_strlen(tmp)+1)
	{
		dest[i] = tmp[i];
		i++;
	}
	return (dest);
}
