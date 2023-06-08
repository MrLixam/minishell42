/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:22:33 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:02:43 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	count;
	int	start;
	int	i;

	if (!s1)
		return (ft_calloc(0, 0));
	i = ft_strlen(s1);
	count = 0;
	start = 0;
	while (ft_strchr(set, s1[start++]))
		count++;
	while (ft_strchr(set, s1[i--]))
		count++;
	return (ft_substr(s1, start - 1, ft_strlen(s1) + 1 - count));
}
