/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:43 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/31 03:37:47 by lvincent         ###   ########.fr       */
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
				heredoc_interrupt(delim);
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
	free(delim);
}

static void	heredoc_fork_logic(t_local *local, int fd, char *delim)
{
	signal(SIGINT, sig_heredoc);
	get_input(fd, delim);
	close(fd);
	if (!g_sig)
		exit_command(local, 0);
	exit_command(local, 130);
}

static int	fork_heredoc(int fd, char *delim, t_local *local)
{
	int		pid;
	int		i;

	pid = fork();
	i = 0;
	if (pid == -1)
	{
		perror("minishell : error while parsing heredoc");
		return (1);
	}
	else if (!pid)
		heredoc_fork_logic(local, fd, delim);
	else
	{
		signal(SIGINT, sig_child);
		waitpid(pid, &i, 0);
		signal(SIGINT, sig_parent);
	}
	return (i);
}

static int	create_heredoc_file(char *delim, t_list *curr, t_local *local)
{
	int		fd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strmerge(ft_strdup("/tmp/.heredoc"), ft_itoa(i));
	while (!access(tmp, F_OK))
	{
		free(tmp);
		tmp = ft_strmerge(ft_strdup("/tmp/.heredoc"), ft_itoa(++i));
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
	i = fork_heredoc(fd, delim, local);
	close(fd);
	return (i);
}

int	heredoc(t_local *local)
{
	t_list	*curr;
	t_data	*line;
	char	*delim;
	int		i;

	line = local->data;
	while (line)
	{
		curr = line->redir;
		while (curr)
		{
			if (ft_strncmp(curr->content, "<<", 2) == 0)
			{
				curr = curr->next;
				delim = ft_strdup(curr->content);
				i = create_heredoc_file(delim, curr, local);
				free(delim);
				if (i)
					return (i);
			}
			curr = curr->next;
		}
		line = line->next;
	}
	return (0);
}
