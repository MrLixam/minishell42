/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:57:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 12:57:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>

void	close_pipe(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

void	exit_command(t_local *local, t_data *curr, int fd[3], int code)
{
	int	pipes[2];

	pipes[0] = fd[0];
	pipes[1] = fd[1];
	close_pipe(pipes);
	if (curr != local->data)
		close(fd[2]);
	exit(clear_local(local, code));
}

int	fix_path(t_local *local, t_data *c)
{
	char	*pat;
	char	**tab;
	char	*tmp;
	int		i;

	if ((c->command[0] == '.' && c->command[1] == '/') || c->command[0] == '/')
		return (0);
	pat = ft_getenv(local, "PATH");
	if (!pat)
		return (1);
	tab = ft_split(pat, ':');
	i = -1;
	while (tab[++i])
	{
		tmp = ft_strmerge(ft_strjoin(tab[i], "/"), ft_strdup(c->command));
		if (!access(tmp, F_OK))
		{
			free(c->command);
			c->command = tmp;
			freetab(tab);
			return (0);
		}
		free(tmp);
	}
	freetab(tab);
	return (1);
}
