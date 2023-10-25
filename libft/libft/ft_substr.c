/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:10:00 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/25 19:37:22 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (malloc(0));
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = ft_calloc(len + 1, 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
