/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:31 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:10:38 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

enum					e_words_types
{
	word,
	sq_word,
	dq_word,
	r_redirect,
	l_redirect,
	here_doc,
	append,
	pi_pe,
	space
};
typedef struct s_norm
{
	char				*var;
	char				*cont;
}						t_norm;

typedef struct s_global
{
	int					exit_status;
	int					echo_status;
}						t_global;

typedef struct s_list_env
{
	char				*variable;
	char				*content;
	int					c;
	struct s_list_env	*next;
}						t_list_env;

typedef struct s_infos
{
	int					n_pipes;
	int					is_quote;
	int					flag;
	int					pos;
	int					start;
	int					len;
	int					is_finish;
	int					index;
	int					n_red;
	int					*fds;
	t_list_env			*env;
}						t_infos;

typedef struct s_cmd_lines
{
	char				**cmd_line;
	int					infile;
	int					outfile;
	t_infos				*infos;
	struct s_cmd_lines	*next;
}						t_cmd_lines;

typedef struct s_data
{
	char				*word;
	int					tfree;
	int					id;
	int					type;
	char				**vars;
	int					exp;
	t_infos				*infos;
	int					fd_here_doc;
	struct s_data		*next;
}						t_data;

extern t_global			*g_global;

char					*getpath(char **env);
t_data					*lexer(char *str, t_infos *infos);
char					*ft_substr_parse(char const *s, t_infos *infos);
//linked_list
void					ft_lstadd_back(t_data **lst, t_data *new);
int						ft_lstsize(t_data *lst);
t_data					*ft_lstlast(t_data *lst);
t_data					*ft_lstnew(char *content, t_infos *infos);
//cleaners
void					clean_list(t_data **lst_words);
int						syntaxe_checker(t_data *cmd_line);
// void    get_the_dollar(t_data   *cmd_line);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strrchr_env(const char *s, int c);
// int	builts_in(t_cmd_lines *cmd, t_list_env **env);
t_cmd_lines				*ft_lstnew_exp(char **content, int in_fd, int out_fd,
							t_infos *infos);
void					ft_lstadd_back_exp(t_cmd_lines **lst, t_cmd_lines *new);
void					split_line(t_data *cmd_line);
t_cmd_lines				*ft_lstlast_exp(t_cmd_lines *lst);
void					the_fucking_expand(t_data *lst_words);
void					here_doc_func(t_data *lst_words);
char					*expand_in_hd(char *str, t_list_env *env);
char					*two_to_one(char **vars);
void					freealloc2(char **ptr);
t_cmd_lines				*join_words(t_data *lst_words);
int						delete_adds(t_cmd_lines **lines);
//  START built fonctions '_'
t_list_env				*ft_lstlast_env(t_list_env *lst);
void					ft_lstadd_back_env(t_list_env **lst, t_list_env *new);
t_list_env				*ft_lstnew_env(char *content, char *variable, int flag);
void					grep_env(char **env, t_list_env **enev);
int						check_equal(char *env);
int						check_n(char *av);
char					*print_env(t_list_env **env, char *var);
void					change_env(t_list_env **env, char *var, char *cont);
int						check_env(t_list_env *env, char *var);
int						pars_export(char *av);
int						built_echo(char **av, int fd);
int						built_env(t_list_env *enev, int fd);
int						built_unset(t_list_env *enev, char **av);
int						built_pwd(t_list_env **env, int fd);
int						builts_in(t_cmd_lines *cmd, t_list_env **enev,
							int flag);
int						built_cd(t_list_env *env, char **args);
int						built_export(t_list_env *env, char **av, int fd);
// END built fonctions '_'
char					*path_split(t_cmd_lines *env);
int						ft_execution(t_cmd_lines *lines, int fd[2]);
void					rl_replace_line(const char *text, int clear_undo);
long					ft_atoi_overflow(char *str);
void					clean_in_exit(t_list_env **env, t_global *g_global);

t_cmd_lines				*parsing(char *str, t_infos *infos);
void					execution(t_cmd_lines *lines, t_infos *infos, int c);
void					tby_shell(char *str, t_infos *infos);
void					clean_lines2(t_cmd_lines **lines);
int						is_redrect(char *str);
int						is_built(t_cmd_lines *cmd);
//ecp utils
int						check_prev(t_data *lst_words, int id);
int						check_next_2hd(t_data *lst_words, int id);
void					set_ids(t_data *lst_words);
int						count_words(char *str);
int						get_len(char *str, int *i);
char					*expand(t_list_env *env);
char					*skip_space(char *str);
int						len_of_space(char *str);
int						dollar_in(char *str);
int						space_in(char *str);
void					fill_vars2(t_data *cmd_line, char *tmp, int j,
							t_data *head);
int						len_of_word(char *str, int *i);
int						dollar_len(char *str, int *i);
int						white_sp_len(char *str, int *i);
char					*set_value(char *var, t_list_env *env);
//lexer
int						all_spaces(t_data *words);
int						quoting_checker(char *str);
int						strat_end_checker(char *str);
int						quote_len(char *str, t_infos *infos);
int						white_sp(char *str, t_infos *infos);
int						conditions(t_infos *infos, char *str, int *i, int *len);
int						word_len(char *str, t_infos *infos);
void					init_args(t_infos *infos);
int						count_red(t_data *lst_words);
int						is_expandable(t_data *lst_words);
//here_doc
char					*get_tmp(void);
int						count_hrdc(t_data *lst_words);
void					c_handl(int sig);
void					sig_d(t_data *lst_words);
void					fill_here_doc(int fd, t_data *del, t_data *lst_words);
t_data					*join_del(t_data *lst_words);
//parser
int						count_w(t_data *lst_words);
char					*join(t_data *lst_words, int *id);
int						fill_vars3(t_data **lst_words, int *i, char **vars,
							int *fd);
void					initvr(t_data **head, int *i, int *fd,
							t_data *lst_words);
// red
int						get_type(t_cmd_lines *line);
int						is_red(char *str);
void					set_fd(int **fds, int fd);
int						priority(char **vars, int i);
int						inred(t_cmd_lines *lines, int i);
int						outred(t_cmd_lines *lines, int i);
int						appendred(t_cmd_lines *lines, int i);
int						redirections(t_cmd_lines *lines, int i);
int						open_file(t_cmd_lines *lines);
int						get_new_lenght(char **vars);
int						vars_len(char **vars);
char					**delete_red(t_cmd_lines *lines);
void					clean_lines(t_cmd_lines **lines);
int						strs_len(char **str);
char					**ft_strdup2(char **strs);
//error centre
int						check_for_errors(int *types, int len);
int						conditions2(int *types, int j, int i, int len);
void					open_err(char *file_name, int code);
void					print_error(int code, int type);
void					print_code_0(int type);
//builts export
void					exprt_no_args(t_list_env *env, int fd);
void					concat(t_list_env **env, char *var, char *cont);
void					set_var(t_list_env **env, char *var, char *cont);
void					print_exprt_err(char *str);
void					ft_export(char **av, int i, t_list_env **env,
							t_norm *chars);
//built exit
int						built_exit(t_cmd_lines *cmd, int flag);
//exec
char					**convert_env(t_list_env *env, char **envp, int i);
char					*join_args(t_cmd_lines *cmd);
void					err_file(char *str);
void					err_cmd(char *str);
char					*get_binary(char **split, char *str);
void					err_127(char *str, DIR *dir);
int						execve_fail(char *path, t_cmd_lines *lines);
void					ft_wait(t_cmd_lines *lines, int pid, int old, int fd);
void					fds_manager(t_cmd_lines *lines, int *fd, int old);

#endif
