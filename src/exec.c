/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/17 01:52:39 by marvin           ###   ########.fr       */
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

int	is_builtin(char *command)
{
	int	l;

	l = ft_strlen(command);
	return (!ft_strncmp(command, "echo", l) || !ft_strncmp(command, "cd", l)
		|| !ft_strncmp(command, "pwd", l) || !ft_strncmp(command, "export", l)
		|| !ft_strncmp(command, "unset", l) || !ft_strncmp(command, "env", l)
		|| !ft_strncmp(command, "exit", l));
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

int	perror_filename(char *command, char *filename)
{
	char	*err;

	err = ft_strjoin(command, filename);
	perror(err);
	free(err);
	return (-1);
}

static int	redir_in(t_data *command, int in)
{
	t_list	*input;
	int		i;

	input = command->input;
	if (!input)
		return (in);
	i = 0;
	while (input->next)
	{
		if (i % 2 != 0 && file_access(input->content))
			return (perror_filename("minishell :", input->content));
		input = input->next;
		i++;
	}
	if (!file_access(input->content))
		return (open(input->content, O_RDONLY));
	return (perror_filename("minishell :", input->content));
}

static int	redir_out(t_data *command, int out)
{
	t_list	*output;
	int		i;
	int		fd;
	char	*tmp;

	output = command->output;
	if (!output)
		return (out);
	i = 1;
	tmp = ft_strdup(output->content);
	output = output->next;
	while (output)
	{
		if (i % 2 != 0)
		{
			if (ft_strlen(tmp) == 1)
				fd = open(output->content, O_CREAT | O_TRUNC | O_RDWR, 0644);
			else
				fd = open(output->content, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (fd == -1)
				return (perror_filename("minishell :", output->content));
			if (output->next)
				close(fd);
		}
		else
		{
			free(tmp);
			tmp = ft_strdup(output->content);
		}
		output = output->next;
		i++;
	}
	free(tmp);
	return (fd);
}

static void	link_redir(int pipes[2], int fd, t_data *curr, t_group *group)
{
	int	redir[2];

	if (curr == *group->line && curr->next == NULL)
		return ;
	redir[0] = redir_in(curr, fd);
	redir[1] = redir_out(curr, pipes[1]);
	if (redir[0] == -1 || redir[1] == -1)
	{
		perror("minishell: ");
		clean_child(group, curr, pipes, fd);
	}
	if (curr != *group->line && curr->next != NULL)
	{
		dup2(redir[0], STDIN_FILENO);
		dup2(redir[1], STDOUT_FILENO);
		close(redir[0]);
		close_pipe(pipes);
	}
	else if (curr == *group->line)
	{
		dup2(redir[1], STDOUT_FILENO);
		close(redir[1]);
		close(pipes[0]);
	}
	else if (curr->next == NULL)
	{
		dup2(redir[0], STDIN_FILENO);
		close(redir[0]);
	}
}

int	redir_present(t_data *command)
{
	return (command->output != NULL || command->input != NULL);
}

void	fix_path(t_data **line)
{
	char	*path;
	char	**path_tab;
	char	*tmp;
	int		i;

	path = getenv("PATH");
	if (path == NULL || file_access((*line)->command) == 0)
		return ;
	path_tab = ft_split(path, ':');
	i = 0;
	while (path_tab[i])
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
			return ;
		}
		i++;
	}
	freetab(path_tab);
}

void	exec_builtin(char *command, char **str, t_list *arg)
{
	int len;

	len = ft_strlen(command);
	if (!ft_strncmp(command, "echo", len))
		ft_echo(arg);
	else if (!ft_strncmp(command, "cd", len))
		ft_cd(str);
	else if (!ft_strncmp(command, "pwd", len))
		ft_pwd();
	/*else if (!ft_strncmp(command, "export", len))
		ft_export(str);
	else if (!ft_strncmp(command, "unset", len))
		ft_unset(str);
	else if (!ft_strncmp(command, "env", len))
		ft_env();*/
	else if (!ft_strncmp(command, "exit", len))
		exit(0);
}

static void	do_logic(int pipes[2], int fd, t_data *curr, t_group *group)
{
	char	**str;

	link_redir(pipes, fd, curr, group);
	str = lst_to_str(curr->arg, curr->command);
	if (is_builtin(curr->command))
	{
		exec_builtin(curr->command, str, curr->arg);
		return ;
	}
	fix_path(&curr);
	execve(curr->command, str, g_env);
	freetab(str);
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

static void	pipeline(t_group *group)
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

void	redir_single(t_data *line)
{
	int	redir[2];

	redir[0] = redir_in(line, STDIN_FILENO);
	redir[1] = redir_out(line, STDOUT_FILENO);
	if (redir[0] != STDIN_FILENO)
	{
		dup2(redir[0], STDIN_FILENO);
		close(redir[0]);
	}
	if (redir[1] != STDOUT_FILENO)
	{
		dup2(redir[1], STDOUT_FILENO);
		close(redir[1]);
	}
}

static void	no_pipe(t_data *line)
{
	char	**str;
	int		pid;
	int		ret;

	str = lst_to_str(line->arg, line->command);
	if (is_builtin(line->command))
	{
		redir_single(line);
		exec_builtin(line->command, str, line->arg);
		return ;
	}
	pid = fork();
	if (pid < 0)
		perror("minishell: fork failed");
	else if (!pid)
	{
		redir_single(line);
		fix_path(&line);
		execve(line->command, str, g_env);
		perror_filename("minishell :", line->command);
	}
	else
		waitpid(pid, &ret, 0);
	freetab(str);
}

void	exec(t_data *line)
{
	t_group	*group;
	int		i;
	int		ret;

	if (data_len(line) > 1)
	{
		group = ft_calloc(1, sizeof(t_group));
		group->child_pid = ft_calloc(data_len(line), sizeof(int));
		group->line = &line;
		pipeline(group);
		i = 0;
		while (i < data_len(line))
			waitpid(group->child_pid[i++], &ret, 0);
		free(group->child_pid);
		free(group);
	}
	else
		no_pipe(line);
}
