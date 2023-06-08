/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:29:24 by gpouzet           #+#    #+#             */
/*   Updated: 2022/11/18 18:50:16 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_hexa(unsigned long long nbr, char *base)
{
	size_t	size;

	size = 0;
	if (nbr >= 16)
	{
		size += ft_hexa(nbr / 16, base);
		size += ft_char(base[nbr % 16], 0);
		return (size);
	}
	return (ft_char(base[nbr], 0));
}

static int	ft_hexabsize(unsigned long long nbr, char *base)
{
	size_t	size;

	size = 0;
	if (nbr >= 16)
	{
		size += ft_hexabsize(nbr / 16, base);
		size += 1;
		return (size);
	}
	return (1);
}

int	ft_adress(unsigned long long p, int bonus)
{
	int	size;

	if (p == 0)
		return (ft_string("(nil)", bonus, -1));
	size = ft_hexabsize(p, "0123456789abcdef");
	if (bonus > 0)
		size += ft_space(bonus - size - 2, ' ');
	ft_putchar_fd('0', 1);
	ft_putchar_fd('x', 1);
	size += 2;
	ft_hexa(p, "0123456789abcdef");
	if (-bonus > 0)
		size += ft_space(-bonus - size, ' ');
	return (size);
}

int	ft_lowhexa(unsigned int i, int pad[3], int hash)
{
	size_t	size;

	if (i == 0 && pad[1] == 0)
		return (ft_space(ft_abs(pad[0]), ' '));
	size = ft_hexabsize(i, "0123456789abcdef");
	if (hash && i)
		size += 2;
	size += ft_phase_one(size, pad[0], pad[1], pad[2]);
	if (pad[0] > 0 && pad[2] == 1 && pad[0] >= pad[1])
		size += ft_space(pad[0] - size, '0');
	else if (pad[1] > 0 && pad[1] != pad[0])
		size += ft_space(pad[1] - ft_hexabsize(i, "0123456789abcdef"), '0');
	if (hash && i)
		ft_string("0x", -1, -1);
	ft_hexa(i, "0123456789abcdef");
	if (-pad[0] > 0)
		size += ft_space(-pad[0] - size, ' ');
	return (size);
}

int	ft_upphexa(unsigned int i, int pad[3], int hash)
{
	size_t	size;

	if (i == 0 && pad[1] == 0)
		return (ft_space(ft_abs(pad[0]), ' '));
	size = ft_hexabsize(i, "0123456789ABCDEF");
	if (hash && i)
		size += 2;
	size += ft_phase_one(size, pad[0], pad[1], pad[2]);
	if (pad[0] > 0 && pad[2] == 1 && pad[0] >= pad[1])
		size += ft_space(pad[0] - size, '0');
	else if (pad[1] > 0 && pad[1] != pad[0])
		size += ft_space(pad[1] - ft_hexabsize(i, "0123456789ABCDEF"), '0');
	if (hash && i)
		ft_string("0X", -1, -1);
	ft_hexa(i, "0123456789ABCDEF");
	if (-pad[0] > 0)
		size += ft_space(-pad[0] - size, ' ');
	return (size);
}
