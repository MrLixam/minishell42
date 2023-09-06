/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <gpouzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:15:04 by gpouzet           #+#    #+#             */
/*   Updated: 2023/09/06 17:07:50 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"

char	*fr_realloc(char *src, int size)
{
	char	*tmp;

	tmp = malloc(size);
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, src, ft_strlen(src));
	free(src);
	return (tmp);
}
