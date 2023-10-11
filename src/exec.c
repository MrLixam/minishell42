/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/11 13:32:16 by lvincent         ###   ########.fr       */
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
	close_pipe(pipes);
	if (curr != *group->line)
		close(fd);
	clear_data(*group->line);
	free(group->child_pid);
	free(group);
	g_error = 1;
	exit(EXIT_FAILURE);
}

static int	redir_in(t_data *command)
{
	t_list *input;
	int		i;
	char	*err;

	input = command->input;
	if (!input)
		return (STDIN_FILENO);
	i = 0;
	while (input->next)
	{
		if ((i % 2 != 0 && file_access(input->content))
		{
			err = ft_strjoin("minishell: ", input->content);
			perror(err);
			free(err);
			return (-1);
		}
		input = input->next;
	}
	if (!file_access(input->content))
		return (open(input->content, O_RDONLY));
	err = ft_strjoin("minishell: ", input->content);
	perror(err);
	free(err);
	return (-1);
}

static int	redir_out(t_data *command)
{
	t_list *output;
	int		i;
	int		fd;
	char 	*mode;

	output = command->output;
	if (!output)
		return (STDOUT_FILENO);
	i = 0;
	mode = ft_strdup("");
	while (output)
	{
		if ((i % 2 != 0)
		{
			if (ft_strlen(mode) == 2)
				open
			if (output->next && fd != -1)
				close(fd);
		}
		else
		{
			free(mode);
			mode = ft_strdup(output->content);
		}
		output = output->next;
	}
}

static void no_redir(int pipes[2], int fd, t_data *curr, t_group *group)
{
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
	else if (curr->next == NULL)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	link_redir(int pipes[2], int fd, t_data *curr, t_group *group)
{	
	int	redir[2];

	redir[0] = redir_in(curr);
	redir[1] = redir_out(curr);
	if (redir[0] == -1 || redir[1] == -1)
	{
		perror("minishell: ");
		clean_child(group, curr, pipes, fd);
	}
	if (curr != *group->line && curr->next != NULL)
	{
		dup2(fd, redir[0]);
		dup2(pipes[1], redir[1]);
		close(fd);
		close_pipe(pipes);
	}
	else if (curr == *group->line)
	{
		dup2(pipes[1], redir[1]);
		close_pipe(pipes);
	}
	else if (curr->next == NULL)
	{
		dup2(fd, redir[0]);
		close(fd);
	}
}

int	redir_present(t_data *command)
{
	return (command->output != NULL || command->input != NULL);
}

static void	do_logic(int pipes[2], int fd, t_data *curr, t_group *group)
{
	char	**str;

	if (!redir_present(curr))
		no_redir(pipes, fd, curr, group);
	else
		link_redir(pipes, fd, curr, group);
	str = lst_to_str(curr->arg, curr->command);
	if (file_access(curr->command))
		execve(curr->command, str, g_env);
	freetab(str);
	perror("minishell: execve:");
	clean_child(group, curr, pipes, fd);
}

static void	ft_error(char *message, t_group *group)
{
	perror(message);
	clear_data(*group->line);
	free(group);
	free(group->child_pid);
	g_error = 1;
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
	g_error = 0;
	while (curr && !g_error)
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