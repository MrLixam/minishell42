/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/01 01:11:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static void	close_pipe(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

static char	**lst_to_str(t_list *lst, char *command)
{
	char	**str;
	int		i;

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

static void	clean_child(t_group *group, t_data *curr, int pipes[2], int fd)
{
	close(pipes[0]);
	close(pipes[1]);
	if (curr != *group->line)
		close(fd);
	clear_data(*group->line);
	free(group->child_pid);
	free(group);
	exit(EXIT_FAILURE);
}

static void	do_logic(int pipes[2], int fd, t_data *curr, t_group *group)
{
	char	**str;

	if (curr != *group->line && curr->next != NULL)
	{
		dup2(fd, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(fd);
		close_pipe(pipes);
	}
	else if (curr == *group->line)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close_pipe(pipes);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	str = lst_to_str(curr->arg, curr->command);
	execve(curr->command, str, group->envp);
	freetab(str);
	perror("minishell: execve:")
	clean_child(group, curr, pipes, fd);
}

static void	ft_error(char *message, t_group *group)
{
	perror(message);
	clear_data(*group->line);
	free(group);
	exit(EXIT_FAILURE);
}

static void	p_pass(t_group *group, t_data **curr, int *fd, int pipes[2])
{
	if (*curr != *group->line)
		close(*fd);
	if ((*curr)->next != NULL)
	{
		*fd = pipes[0];
		close(pipes[1]);
	}
	*curr = (*curr)->next;
}

void	pipeline(t_group *group)
{
	int		pipes[2];
	int		fd_pid[2];
	int		i;
	t_data	*curr;

	curr = *group->line;
	fd_pid[0] = STDIN_FILENO;
	i = 0;
	while (curr)
	{
		if (pipe(pipes) == -1)
			ft_error("-minishell: pipe failed", group);
		fd_pid[1] = fork();
		if (fd_pid[1] < 0)
			ft_error("-minishell: fork failed", group);
		else if (!fd_pid[1])
			do_logic(pipes, fd_pid[0], curr, group);
		else
		{
			p_pass(group, &curr, &fd_pid[0], pipes);
			group->child_pid[i++] = fd_pid[1];
		}
	}
	close_pipe(pipes);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_data		*line;
	t_group		*group;

	group = ft_calloc(1, sizeof(t_group));
	group->line = &line;
	group->envp = envp;
	line = new_data();
	line->command = ft_strdup("/bin/ls");
	line->arg = ft_lstnew(ft_strdup("-l"));
	line->next = new_data();
	line->next->command = ft_strdup("/bin/echo");
	line->next->arg = ft_lstnew(ft_strdup("$?"));
	line->next->next = NULL;
	group->child_pid = ft_calloc(data_len(line), sizeof(int));
	pipeline(group);
	while (wait(NULL) > 0)
		;
	clear_data(line);
	free(group->child_pid);
	free(group);
	return (0);
} */
