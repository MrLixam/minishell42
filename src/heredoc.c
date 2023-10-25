/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:43 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/25 19:23:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_input(int fd, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strmcmp(line, delim))
		{
			if (line == NULL)
			{
				ft_putstr_fd("minishell: warn: heredoc end by EOF (want `", 2);
				ft_putstr_fd(delim, 2);
				ft_putstr_fd("')\n", 2);
			}
			free(line);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		line = ft_strmerge(line, ft_strdup("\n"));
		write(fd, line, ft_strlen(line));
		free(line);
	}
	write(fd, "\n", 1);
}

static int	fork_heredoc(int fd, char *delim)
{
	int		pid;
	int		i;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell : error while parsing heredoc");
		return (1);
	}
	else if (!pid)
	{
		signal(SIGINT, sig_heredoc);
		*getfd() = fd;
		get_input(fd, delim);
		close(fd);
		*getfd() = -1;
		exit(0);
	}
	else
	{
		signal(SIGINT, sig_child);
		waitpid(pid, &i, 0);
		signal(SIGINT, sig_parent);
	}
	return (i);
}

static int	create_heredoc_file(char *delim, t_list *curr)
{
	int		fd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin("/tmp/.heredoc", ft_itoa(i));
	while (!access(tmp, F_OK))
	{
		free(tmp);
		tmp = ft_strjoin("/tmp/.heredoc", ft_itoa(++i));
	}
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(curr->content);
	curr->content = ft_strdup(tmp);
	free(tmp);
	if (fd == -1)
	{
		perror("minishell : error while parsing heredoc");
		return (1);
	}
	i = fork_heredoc(fd, delim);
	close(fd);
	return (i);
}

int	heredoc(t_data **line)
{
	t_list	*curr;
	t_data	*local;
	char	*delim;
	int		i;

	local = *line;
	while (local)
	{
		curr = local->input;
		while (curr)
		{
			if (ft_strncmp(curr->content, "<<", 2) == 0)
			{
				curr = curr->next;
				delim = ft_strdup(curr->content);
				i = create_heredoc_file(delim, curr);
				free(delim);
				if (i)
					return (i);
			}
			curr = curr->next;
		}
		local = local->next;
	}
	return (0);
}
