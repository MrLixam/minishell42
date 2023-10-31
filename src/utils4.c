/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:42:49 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/31 03:38:12 by lvincent         ###   ########.fr       */
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

void	heredoc_interrupt(char *delim)
{
	ft_putstr_fd("minishell: warn: heredoc end by EOF (want `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}

void	no_command_pipe(t_local *local, int pipes[2], t_data *curr, int fd)
{
	link_redir(pipes, fd, curr, local);
	exit_command(local, 0);
}