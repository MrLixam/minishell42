/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:50:15 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 16:50:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *getfd(void)
{
	static int	fd = -1;
	return (&fd);
}

/*int *heredoc_sig(void)
{
	static int	sig = 1;
	return (&sig);
}*/