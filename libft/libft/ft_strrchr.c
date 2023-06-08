/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:59:13 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:02:28 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str) + 1;
	while (c > 256)
		c -= 256;
	while (i-- > 0)
		if (str[i] == c)
			while (i-- > 0)
				str++;
	if (*str == c)
		return ((char *)str);
	return (0);
}
