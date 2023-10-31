/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:42:49 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/31 02:52:57 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset(char *tmp)
{
	if (tmp)
		free(tmp);
	return (1);
}

char	*ft_realloc_string(char *old, char *new)
{
	free(old);
	return (new);
}
