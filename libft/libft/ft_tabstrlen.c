/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:36:29 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/28 19:24:04 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_tabstrlen(char **arg)
{
	size_t	i;

	if (!arg)
		return (0);
	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}
