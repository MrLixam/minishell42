/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:51:08 by gpouzet           #+#    #+#             */
/*   Updated: 2022/11/22 16:44:56 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_nbr(unsigned int nb, int bonus)
{
	if (nb < 10)
		return (ft_char(nb + '0', bonus));
	return (ft_nbr(nb / 10, 0) + ft_char(nb % 10 + '0', 0));
}

static int	ft_nbr_size(unsigned int nb)
{
	if (nb < 10)
		return (1);
	return (ft_nbr_size(nb / 10) + 1);
}

int	ft_int(int i, int pad[3], int btwo[3])
{
	size_t	size;

	if (pad[1] == 0 && i == 0)
		return (ft_space(ft_abs(pad[0]), ' '));
	size = ft_nbr_size(ft_abs(i));
	if (i < 0 || btwo[2])
		size++;
	if (btwo[1] && i >= 0 && !btwo[2])
		size += ft_space(1, ' ');
	if ((i < 0 && pad[1] > (int)size && i != -2147483648) || btwo[1] || btwo[2])
			pad[0]--;
	size += ft_phase_one(size, pad[0], pad[1], pad[2]);
	if (i < 0 && pad[2] == 1 && pad[1] > 0 && i != -2147483648)
		size--;
	ft_sign(i, btwo[2]);
	if (pad[0] > 0 && pad[2] == 1 && pad[0] >= pad[1])
		size += ft_space(pad[0] - size, '0');
	else if (pad[1] > 0)
		size += ft_space(pad[1] - ft_nbr_size(ft_abs(i)), '0');
	if (i < 0 && pad[2] == 1 && pad[1] > 0 && i != -2147483648)
		size++;
	ft_nbr(ft_abs(i), 0);
	if (-pad[0] > 0)
		size += ft_space(-pad[0] - size, ' ');
	return (size);
}

int	ft_unsigned(unsigned int ui, int mini, int maxi, int pad)
{
	size_t	size;

	if (maxi == 0 && ui == 0)
		return (ft_space(ft_abs(mini), ' '));
	size = ft_nbr_size(ui);
	size += ft_phase_one(size, mini, maxi, pad);
	if (mini > 0 && pad == 1 && mini >= maxi)
		size += ft_space(mini - size, '0');
	else if (maxi > 0 && maxi != mini)
		size += ft_space(maxi - ft_nbr_size(ui), '0');
	ft_nbr(ui, 0);
	if (-mini > 0)
		size += ft_space(-mini - size, ' ');
	return (size);
}
