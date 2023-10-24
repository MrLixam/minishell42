/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:59:09 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/24 15:42:41 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/printf.h"
# include "../libft/list.h"
# include "../libft/get_next_line.h"

/*			global			*/
extern int		g_exit;
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
	t_list			*input;
	t_list			*output;
	t_list			*arg;
	struct s_data	*next;
}	t_data;

/*			prototype		*/
int		ft_strmcmp(char *s1, char *s2);
int		clear_local(t_local	*local, int exit_code);

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
int		redirection(char *lexer, t_data *data);
char	**pre_parser(char *lexer);
char	**arg_sep(char const *s);
char	**env_sep(char const *s);
t_data	*switch_elem(char **lexer, t_data *first);
char	*ft_strmerge(char *s1, char *s2);

/*			exec			*/
void	exec(t_local *local);

/*			builtins		*/
int		ft_pwd(void);
int		ft_cd(t_local *local, char **arg);
int		ft_echo(t_list *arg);
int		ft_export(t_local *local, char **arg);
int		ft_unset(t_local *local, char **arg);
void	ft_exit(t_local *local);

/*			env_modif		*/
char	*ft_getenv(t_local *local, char *name);
int		create_env(t_local *local, char **envp);
int		unset_env(t_local *local, char *unset);
int		export_env(t_local *local, char *env);
int		print_env(t_local *local, char **arg);

/*			error			*/
int		perror_filename(char *command, char *filename);
int		ft_error(char *message, t_local *local);
void	path_error(char *filename);

/*			execution		*/
void	link_redir(int pipes[2], int fd, t_data *curr, t_local *local);
int		is_builtin(char *command);
int		file_access(char *path);
char	**lst_to_str(t_list *lst, char *command);
int		redir_present(t_data *command);
int		exec_builtin(t_local *local, char **str, t_data *line);
int		fix_path(t_local *local, t_data *curr);
void	clean_child(t_local *local, t_data *curr, int pipes[2], int fd);
void	close_pipe(int pipes[2]);
void	redirect(int in, int out, t_data *curr, int redir[2]);
int		pipeline(t_local *local);

#endif
