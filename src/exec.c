/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/09/21 01:10:25 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

static char **lst_to_str(t_list *lst, char *command)
{
	char **str;
	int i;

	i = 0;
	str = ft_calloc(ft_lstsize(lst) + 2, sizeof(char *));
	str[0] = ft_strdup(command);
	i++;
	while (lst)
	{
		str[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	return (str);
}

static int	file_access(char *path)
{
	return (access(path, F_OK & R_OK & W_OK & X_OK));
}

void pipeline(t_data **line, char **envp)
{
	int pipes[2];
	int fd;
	int pid;
	t_data *curr;
	char **str;

	curr = *line;
	fd = STDIN_FILENO;
	while (curr)
	{
		if (pipe(pipes) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (!pid)
		{
			if (curr != *line && curr->next != NULL)
			{
				dup2(fd, STDIN_FILENO);
				dup2(pipes[1], STDOUT_FILENO);
				close(fd);
				close(pipes[0]);
				close(pipes[1]);
			}
			else if (curr == *line)
			{
				dup2(pipes[1], STDOUT_FILENO);
				close(pipes[0]);
				close(pipes[1]);
			}
			else
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			str = lst_to_str(curr->arg, curr->command);
			execve(curr->command, str, envp);
			freetab(str);
		}
		else
		{
			if (curr != *line)
				close(fd);
			if (curr->next != NULL)
			{
				fd = pipes[0];
				close(pipes[1]);
			}
			curr = curr->next;
		}
	}
}