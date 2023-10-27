/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/27 12:35:37 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>

int	g_sig;

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

void	reset(t_local *local, char **str)
{
	clear_data(local->data);
	local->child_pid = NULL;
	*str = NULL;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	minishell_loop(t_local *local)
{
	char	*str;
	int		err;

	while (1)
	{
		str = readline("minishell$ ");
		check_sigint(local);
		if (str == NULL)
			return ;
		if (wspace(str))
			continue ;
		if (ft_strncmp(str, "\0", 2))
			add_history(str);
		err = parser(local, str);
		if (err)
			local->exit_code = err;
		if (local->data == NULL || err)
			continue ;
		if (!empty_data(local->data) && local->data->command == NULL)
			local->exit_code = 0;
		if (empty_data(local->data))
			exec(local);
		reset(local, &str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_local	*local;

	g_sig = 0;
	local = ft_calloc(1, sizeof(t_local));
	if (!local)
		return (1);
	init_local(local, envp);
	(void) argc;
	(void) argv;
	signal(SIGINT, sig_parent);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(local);
	freetab(local->env);
	free(local);
	return (0);
}
