/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:05:22 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 12:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_in(char *file)
{
	char	*cut_path;
	int		fd;

	cut_path = ft_strcut(file, "./");
	fd = -1;
	if (!access(cut_path, R_OK))
		if (!access(cut_path, F_OK))
			fd = open(cut_path, O_RDONLY);
	free(cut_path);
	if (fd == -1)
		return (perror_filename("minishell : ", file));
	return (fd);
}

static int	redir_out(char *file, char *tmp)
{
	char	*cut_path;
	int		fd;

	cut_path = ft_strcut(file, "./");
	fd = -1;
	if (ft_strlen(tmp) == 1)
		fd = open(cut_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		fd = open(cut_path, O_CREAT | O_APPEND | O_RDWR, 0644);
	free(cut_path);
	if (fd == -1)
		return (perror_filename("minishell : ", file));
	return (fd);
}

int	redirect_loop_logic(t_list *local_redir, char **tmp, int redir[2], int i)
{
	if (i == 0 || i % 2 == 0)
	{
		free(*tmp);
		*tmp = ft_strdup(local_redir->content);
		return (0);
	}
	else
	{
		if (**tmp == '<')
			redir[0] = redir_in(local_redir->content);
		else if (**tmp == '>')
			redir[1] = redir_out(local_redir->content, *tmp);
	}
	if (redir[0] == -1 || redir[1] == -1)
		return (1);
	if (redir[0] != STDIN_FILENO)
		if (!is_last(local_redir, 0))
			close(redir[0]);
	if (redir[1] != STDOUT_FILENO)
		if (!is_last(local_redir, 1))
			close(redir[1]);
	return (0);
}

void	redirect(int in, int out, t_data *curr, int redir[2])
{
	int		i;
	t_list	*local_redir;
	char	*tmp;
	int		err;

	redir[0] = in;
	redir[1] = out;
	if (!curr->redir)
		return ;
	i = 0;
	local_redir = curr->redir;
	tmp = ft_strdup("");
	while (local_redir)
	{
		err = redirect_loop_logic(local_redir, &tmp, redir, i);
		if (err)
		{
			free(tmp);
			return ;
		}
		local_redir = local_redir->next;
		i++;
	}
	free(tmp);
}

void	link_redir(int pipes[2], int fd, t_data *curr, t_local *local)
{
	int	redir[2];
	int	fds[3];

	fds[0] = pipes[0];
	fds[1] = pipes[1];
	fds[2] = fd;
	redirect(fd, pipes[1], curr, redir);
	if (redir[0] == -1 || redir[1] == -1)
		exit_command(local, fds, 1);
	if (curr->next != NULL || redir[1] != pipes[1])
	{
		dup2(redir[1], STDOUT_FILENO);
		close(redir[1]);
	}
	if (curr != local->data || redir[0] != STDIN_FILENO)
	{
		dup2(redir[0], STDIN_FILENO);
		close(redir[0]);
	}
	close_pipe(pipes);
}
