/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:47:09 by gpouzet           #+#    #+#             */
/*   Updated: 2022/11/12 02:13:08 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_char(char c, int bonus)
{
	size_t	size;

	size = 1;
	if (bonus > 0)
		size += ft_space(bonus - size, ' ');
	ft_putchar_fd(c, 1);
	if (-bonus > 0)
		size += ft_space(-bonus - size, ' ');
	return (size);
}

int	ft_string(char *str, int mini, int maxi)
{
	size_t	size;

	size = 0;
	if (!str && maxi < 6 && maxi >= 0)
		return (0);
	if (!str)
		return (ft_string("(null)", mini, -1));
	if (maxi < 0)
		maxi = ft_strlen(str);
	if (mini > 0)
		size += ft_space(mini - maxi, ' ');
	while (*str && maxi-- > 0)
		size += ft_char(*str++, 0);
	if (-mini > 0)
		size += ft_space(-mini - size, ' ');
	return (size);
}
