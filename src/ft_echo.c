/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:56:53 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 22:56:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(t_list *arg)
{
	int		i;
	int		j;
	char	*str;


	j = 0;
	while (arg)
	{
		str = (char *)arg->content;
		i = 0;
		if (str[i] != '-' || (str[i] == '-' && str[i + 1] != 'n'))
			return (j);
		while (str[++i] == 'n')
			;
		if (str[i])
			return (j);
		j++;
		arg = arg->next;
	}
	return (j);
}

int	ft_echo(t_list *arg)
{
	t_list	*curr;
	int		option;
	int		i;	

	curr = arg;
	option = check_n(curr);
	i = -1;
	while (++i != option)
		curr = curr->next;
	while (curr)
	{
		ft_putstr_fd((char *)curr->content, 1);
		if (curr->next)
			ft_putchar_fd(' ', 1);
		curr = curr->next;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}
