/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/27 00:11:10 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>

static void	init_local(t_local *local, char **envp)
{
	local->child_pid = NULL;
	local->env = NULL;
	local->exit_code = 0;
	create_env(local, envp);
}

static int	wspace(char *c)
{
	int	i;

	i = -1;
	while (c[++i])
		if (!(c[i] >= '\t' && c[i] <= '\r') && c[i] != 32)
			return (0);
	return (1);
}

int	clear_local(t_local	*local, int exit_code)
{
	if (data_len(local->data) <= 1)
		clear_heredoc(local);
	hard_close(1);
	if (local->env)
		freetab(local->env);
	clear_data(local->data);
	if (local->child_pid)
		free(local->child_pid);
	free(local);
	return (exit_code);
}

void	minishell_loop(t_local *local)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (str == NULL)
			return ;
		if (wspace(str))
			continue ;
		if (ft_strncmp(str, "\0", 2))
			add_history(str);
		local->exit_code = parser(local, str);
		if (local->data == NULL || local->exit_code)
			continue ;
		if (empty_data(local->data))
			local->exit_code = 0;
		if (empty_data(local->data))
			exec(local);
		clear_data(local->data);
		local->child_pid = NULL;
		str = NULL;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_local	*local;

	local = ft_calloc(1, sizeof(t_local));
	if (!local)
		return (1);
	init_local(local, envp);
	(void) argc;
	(void) argv;
	minishell_loop(local);
	freetab(local->env);
	free(local);
	return (0);
}
