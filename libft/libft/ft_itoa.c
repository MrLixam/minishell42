/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:37:47 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 12:49:28 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

static int	ft_count(long int nbr)
{
	int	count;

	count = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*convert(char *itoa, long int nbr, int count, int i)
{
	long int	temp;

	while (count > 0)
	{
		temp = nbr / ft_recursive_power(10, --count);
		if (temp < 10)
			itoa[i++] = temp + '0';
		else
			itoa[i++] = temp % 10 + '0';
	}
	itoa[i] = '\0';
	return (itoa);
}

char	*ft_itoa(int nbr)
{
	char		*itoa;
	int			i;
	long int	lnbr;

	i = 0;
	lnbr = (long int)nbr;
	if (lnbr < 0)
	{
		lnbr *= -1;
		itoa = malloc(ft_count(lnbr) + 2);
		if (!itoa)
			return (ft_calloc(0, 0));
		itoa[i++] = '-';
	}
	else
		itoa = malloc(ft_count(lnbr) + 1);
	if (!itoa)
		return (ft_calloc(0, 0));
	return (convert(itoa, lnbr, ft_count(lnbr), i));
}
