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

void	hard_close(int in_child)
{
	int	i;

	if (in_child)
		i = 0;
	else
		i = 3;
	while (i < 1024)
		close(i++);
}

void	exit_command(t_local *local, int code)
{
	hard_close(1);
	exit(clear_local(local, code));
}

int	fix_path(t_local *local, t_data *c)
{
	char	*pat[2];
	char	**tab;
	int		i;

	if ((c->command[0] == '.' && c->command[1] == '/') || c->command[0] == '/')
		return (0);
	pat[0] = ft_getenv(local, "PATH");
	if (!pat[0])
		return (1);
	tab = ft_split(pat[0], ':');
	i = -1;
	free(pat[0]);
	while (tab[++i])
	{
		pat[1] = ft_strmerge(ft_strjoin(tab[i], "/"), ft_strdup(c->command));
		if (!access(pat[1], F_OK))
		{
			free(c->command);
			c->command = pat[1];
			break ;
		}
		free(pat[1]);
	}
	freetab(tab);
	return (c->command[0] != '/');
}

int	*getfd(void)
{
	static int	fd = -1;

	return (&fd);
}
