/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:47:28 by gpouzet           #+#    #+#             */
/*   Updated: 2022/11/22 15:16:58 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include "ft_printf.h"

static int	ft_switch(char c, va_list ap, int pad[3], int btwo[3])
{
	if (c == 'c')
		return (ft_char(va_arg(ap, int), pad[0]));
	if (c == 's')
		return (ft_string(va_arg(ap, char *), pad[0], pad[1]));
	if (c == 'p')
		return (ft_adress(va_arg(ap, unsigned long long), pad[0]));
	if (c == 'd' || c == 'i')
		return (ft_int(va_arg(ap, int), pad, btwo));
	if (c == 'u')
		return (ft_unsigned(va_arg(ap, unsigned int), pad[0], pad[1], pad[2]));
	if (c == 'x')
		return (ft_lowhexa(va_arg(ap, unsigned int), pad, btwo[0]));
	if (c == 'X')
		return (ft_upphexa(va_arg(ap, unsigned int), pad, btwo[0]));
	if (c == '%')
		return (ft_char('%', pad[0]));
	return (0);
}

static int	ft_isflags(char c)
{
	if (c == '.' || c == '-')
		return (1);
	if (c == '#' || c == '+' || c == ' ')
		return (1);
	return (0);
}

static void	bonus_width(const char *str, int pad[3])
{
	pad[0] = 0;
	pad[1] = -1;
	pad[2] = 0;
	while ((*str == '-' && *(str + 1) == '-')
		|| *str == '#' || *str == '+' || *str == ' ')
		str++;
	if ((ft_isdigit(*str) || *str == '-') && *(str + 1) != '#')
		pad[0] = ft_atoi(str);
	else if (ft_isdigit(*str) || *str == '-')
		pad[0] = -1 * ft_atoi(str + 2);
	if (*str == '0')
		pad[2] = 1;
	while (ft_isdigit(*str) || *str == '-')
		str++;
	if (*str == '.')
		pad[1] = ft_atoi(++str);
}

static void	bonus_two(const char *str, int btwo[3])
{
	btwo[0] = 0;
	btwo[1] = 0;
	btwo[2] = 0;
	while (!ft_isalpha(*str))
	{
		if (*str == '#')
			btwo[0] = 1;
		if (*str == ' ')
			btwo[1] = 1;
		if (*str++ == '+')
			btwo[2] = 1;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		size;
	int		pad[3];
	int		btwo[3];

	size = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			bonus_width(++str, pad);
			bonus_two(str, btwo);
			while (ft_isdigit(*str) || ft_isflags(*str))
				str++;
			size += ft_switch(*str++, ap, pad, btwo);
		}
		if (*str && *str != '%')
			size += ft_char(*str++, 0);
	}
	va_end(ap);
	return (size);
}
