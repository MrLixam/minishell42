/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:39:31 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 13:44:55 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"

int				ft_char(char c, int bonus);
int				ft_string(char *str, int mini, int maxi);
int				ft_adress(unsigned long long p, int bonus);
int				ft_int(int i, int pad[3], int btwo[3]);
int				ft_unsigned(unsigned int ui, int mini, int maxi, int pad);
int				ft_lowhexa(unsigned int i, int pad[3], int hash);
int				ft_upphexa(unsigned int i, int pad[3], int hash);
int				ft_space(int n, char c);
int				ft_phase_one(size_t size, int mini, int maxi, int pad);
unsigned int	ft_abs(long int i);
void			ft_sign(int i, int sign);

#endif
