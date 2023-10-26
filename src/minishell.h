/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:59:09 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/26 20:53:51 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/printf.h"
# include "../libft/list.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>

/*			struct			*/
typedef struct s_local
{
	char			**env;
	struct s_data	*data;
	int				*child_pid;
	int				exit_code;
}	t_local;

typedef struct s_data
{
	char			*command;
	t_list			*redir;
	t_list			*arg;
	struct s_data	*next;
}	t_data;

/*			utils		*/
int		ft_strmcmp(char *s1, char *s2);
int		clear_local(t_local	*local, int exit_code);
void	fix_fd(int save[2]);
char	*ft_strcut(char *str, char *set);

/*			signals			*/
void	sig_parent(int sig);
void	sig_child(int sig);
void	sig_heredoc(int sig);

/*			data			*/
t_data	*new_data(void);
int		data_len(t_data *line);
void	freetab(char **tab);
void	clear_data(t_data *data);
int		new_arg(t_list **lst, char *arg);

/*			parser			*/
int		check_quote(char *readline);
int		parser(t_local *local, char *lexer);
int		swap_env_var(t_local *local, char **lex);
int		check_quote(char *readline);
int		format_quote(t_data *current);
int		redirection(char *lexer, t_data *data);
char	**pre_parser(char *lexer);
char	**arg_sep(char const *s);
char	**env_sep(char const *s);
char	*ft_strmerge(char *s1, char *s2);

/*			heredoc			*/
int		heredoc(t_data **line);
int		*getfd(void);
void	clear_heredoc(t_local *local);

/*			builtins		*/
int		ft_pwd(void);
int		ft_cd(t_local *local, char **arg);
int		ft_echo(t_list *arg);
int		ft_export(t_local *local, char **arg);
int		ft_unset(t_local *local, char **arg);
void	ft_exit(t_local *local, char **tab);

/*			env_modif		*/
char	*ft_getenv(t_local *local, char *name);
int		create_env(t_local *local, char **envp);
int		unset_env(t_local *local, char *unset);
int		export_env(t_local *local, char *env);
int		print_env(t_local *local, char **arg);

/*			error			*/
int		perror_filename(char *command, char *filename);
int		ft_error(char *message);
void	ft_cmd_error(char *cmd, char *error, char **str);
void	ft_builtin_error(char *command, char *file, char *error);
int		err_dispatch(char *lex);

/*			execution			*/
void	exec(t_local *local);
char	**lst_to_str(t_list *lst, char *command);
int		fix_path(t_local *local, t_data *curr);

int		is_builtin(char *command);
int		exec_builtin(t_local *local, char **str, t_data *line, int save[2]);

void	redirect(int in, int out, t_data *curr, int redir[2]);
int		redir_present(t_data *command);
void	link_redir(int pipes[2], int fd, t_data *curr, t_local *local);
int		is_last(t_list *redir, int mode);

int		pipeline(t_local *local);
void	exit_command(t_local *local, int code);
void	close_pipe(int pipes[2]);
void	hard_close(int in_child);

#endif
