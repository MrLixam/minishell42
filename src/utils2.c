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

void	clean_child(t_group *group, t_data *curr, int pipes[2], int fd)
{
	close_pipe(pipes);
	if (curr != *group->line)
		close(fd);
	clear_data(*group->line);
	free(group->child_pid);
	free(group);
	exit(errno);
}

int	perror_filename(char *command, char *filename)
{
	char	*err;

	err = ft_strjoin(command, filename);
	perror(err);
	free(err);
	return (-1);
}

int	fix_path(t_data **line)
{
	char	*path;
	char	**path_tab;
	char	*tmp;
	int		i;

	path = getenv("PATH");
	if (path == NULL || file_access((*line)->command) == 0)
		return (0);
	path_tab = ft_split(path, ':');
	i = -1;
	while (path_tab[++i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		free(path_tab[i]);
		path_tab[i] = ft_strjoin(tmp, (*line)->command);
		free(tmp);
		if (!file_access(path_tab[i]))
		{
			free((*line)->command);
			(*line)->command = ft_strdup(path_tab[i]);
			freetab(path_tab);
			return (0);
		}
	}
	freetab(path_tab);
	ft_putstr_fd((*line)->command, 2);
	ft_putendl_fd(": command not found", 2);
	return (1);
}

int	ft_error(char *message, t_group *group)
{
	perror(message);
	clear_data(*group->line);
	free(group);
	free(group->child_pid);
	return (errno);
}
