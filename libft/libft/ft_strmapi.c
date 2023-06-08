/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:49:16 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:01:35 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;

	i = 0;
	if (!s)
		return (ft_calloc(0, 0));
	mapi = ft_calloc(1, ft_strlen(s) + 1);
	if (!mapi)
		return (ft_calloc(0, 0));
	while (s[i])
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	return (mapi);
}
