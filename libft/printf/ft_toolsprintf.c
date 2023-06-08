/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toolsprintf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:27:54 by gpouzet           #+#    #+#             */
/*   Updated: 2022/11/22 15:32:48 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_space(int n, char c)
{
	size_t	s;

	s = 0;
	while (n-- > 0)
		s += ft_char(c, 0);
	return (s);
}

int	ft_phase_one(size_t size, int mini, int maxi, int pad)
{
	if (maxi >= 0 && mini > maxi && (size_t)maxi > size)
		return (ft_space(mini - maxi, ' '));
	else if (mini > 0 && pad == 0 && mini > maxi)
		return (ft_space(mini - size, ' '));
	return (0);
}

void	ft_sign(int i, int sign)
{
	if (i < 0)
		ft_char('-', 0);
	else if (sign)
		ft_char('+', 0);
}

unsigned int	ft_abs(long int i)
{
	unsigned int	tmp;

	tmp = i;
	if (i < 0)
		tmp *= -1;
	return (tmp);
}
