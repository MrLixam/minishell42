/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmputils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:45:29 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/24 12:31:37 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *readline)
{
	int	one;
	int	two;
	int	i;

	i = -1;
	one = 1;
	two = 1;
	while (readline[++i])
	{
		if (readline[i] == 39 && two > 0)
			one *= -1;
		else if (readline[i] == 34 && one > 0)
			two *= -1;
	}
	if (one < 0 || two < 0)
		return (1);
	return (0);
}

char	*ft_strmerge(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}
