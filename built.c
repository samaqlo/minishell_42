/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:37:52 by astalha           #+#    #+#             */
/*   Updated: 2023/06/04 19:05:45 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libc.h"

// #include<libc.h>

t_list_env	*ft_lstlast_env(t_list_env *lst)
{
	t_list_env	*plst;

	if (!lst)
		return (0);
	plst = lst;
	while (plst->next != NULL)
		plst = plst->next;
	return (plst);
}

void	ft_lstadd_back_env(t_list_env **lst, t_list_env *new)
{
	t_list_env	*lastlst;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	lastlst = ft_lstlast_env(*lst);
	lastlst->next = new;
}

t_list_env	*ft_lstnew_env(char *content, char *variable, int flag)
{
	t_list_env	*new;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (!new)
		return (NULL);
	new->variable = ft_strdup(variable);
	new->content = ft_strdup(content);
	new->c = flag;
	new->next = NULL;
	return (new);
}

int	check_equal(char *env)
{
	int	i;

	i = 0;
	if(!env)
		return (0);
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	grep_env(char **env, t_list_env **enev)
{
	int		i;
	int		len;
	int		len_eq;
	char	*content;
	char	*variable;

	i = 0;
	while (env[i])
	{
		len_eq = check_equal(env[i]);
		len = ft_strlen(env[i]);
		variable = ft_substr(env[i], 0, len_eq);
		content = ft_substr(env[i], len_eq + 1, ft_strlen(env[i]) - len_eq);
		ft_lstadd_back_env(enev, ft_lstnew_env(content, variable, 1));
		i++;
		free(variable);
		free(content);
	}
}

int	check_n(char *av)
{
	int	i;

	i = 1;
	if (av[1] != 'n')
		return (1);
	while (av[i])
	{
		if (av[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	built_echo(char **av, int ac)
{
	int	i;
	int	c;
	int	test;

	i = 1;
	test = 1;
	c = 1;
	while (av[i])
	{
		while (!check_n(av[i]) && c)
		{
			test = 0;
			i++;
		}
		c = 0;
		ft_putstr_fd(av[i], ac);
		// printf("%s", av[i++]);
		ft_putstr_fd(" ", ac);
		i++;
	}
	if (test == 1)
		printf("\n");
}


char	*getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 4);
		i++;
	}
	return (NULL);
}
// unset don't remove $pwd $old_pwd $HOME
void	built_env(t_list_env *enev)
{
	while (enev)
	{
		if (enev->c)
		{
			printf("%s", enev->variable);
			printf("=%s\n", enev->content);
		}
		enev = enev->next;
	}
}

void	built_unset(t_list_env *enev, char **av)
{
	int			i;
	t_list_env	*head;

	i = 1;
	head = enev;
	while (av[i])
	{
		while (enev)
		{
			if (!ft_strcmp(av[i], ft_substr(enev->variable, 0,
						ft_strlen(enev->variable))))
				enev->c = 0;
			enev = enev->next;
		}
		enev = head;
		i++;
	}
}
void	change_env(t_list_env **env, char *var, char *cont)
{
	t_list_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var) && tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
			if(!cont)
				tmp->content = ft_strdup("");
			else
				tmp->content = ft_strdup(cont);
		}
		tmp = tmp->next;
	}
	
}
// void	change_env_export(t_list_env **env, char *var, char *cont)
// {
// 	t_list_env	*tmp;

// 	tmp = *env;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->variable, var) && tmp->content)
// 			tmp->content = ft_strdup(cont);
// 		tmp = tmp->next;
// 	}
// }
char	*print_env(t_list_env **env, char *var)
{
	t_list_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var) && tmp->content && tmp->c)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	built_pwd(t_list_env **env)
{
	char	str[1024];

	if (getcwd(str, sizeof(str)))
		printf("%s\n", str);
	else
		printf("%s", print_env(env , "PWD"));
}
void	built_cd(t_list_env *env, char **args)
{
	char	str[1024];
	
	if(!ft_strcmp(args[1], "-"))
	{
		if (print_env(&env, "OLDPWD"))
			printf("%s\n", print_env(&env, "OLDPWD"));
		else
			printf("minishell: cd: OLDPWD not set\n");
	}
	else if (!print_env(&env, "OLDPWD"))
		ft_lstadd_back_env(&env, ft_lstnew_env(print_env(&env, "PWD"), "OLDPWD", 1));
	else if (print_env(&env, "OLDPWD"))
		change_env(&env, "OLDPWD", print_env(&env, "PWD"));
	else if (!args[1])
	{
		if (!print_env(&env, "HOME"))
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		chdir(print_env(&env, "HOME"));
		change_env(&env, "PWD", getcwd(str, sizeof(str)));
	}
	else if (access(args[1], F_OK) == -1)	
		ft_putstr_fd("No such file or directory\n", 2);
	else if (access(args[1], R_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (access(args[1], X_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (args[1])
	{
		chdir(args[1]);
		change_env(&env, "PWD", getcwd(str, sizeof(str)));
	}
}

int	check_env(t_list_env *env, char *var)
{
	int i = 0;
	while(env)
	{
		if(!ft_strcmp(env->variable, var) && env->content)
			return (i);
		i++;
		env = env->next;
	}
	return(0);
}
int	pars_export(char *av)
{
	int i = 0;
	if (av[0] != '_' && ft_isalpha(av[0]) == 0)
		return(0);
	while(av[i] && av[i] != '=')
	{
		if (av[i] == '+' && av[i + 1] == '=')
			return(1);
		if (av[i] != '_' && ft_isalnum(av[i]) == 0)
			return(0);
		i++;
	}
	return(1);
}

void	built_export(t_list_env *env, char **av)
{
	char *var; 
	char *cont;
	char *plus;
	int i = 1;

	if (!av[1])
	{	
		while (env)
		{
			if (env->c)
				printf("declare -x %s=\"%s\"\n", env->variable, env->content);
			else
				printf("declare -x %s\n", env->variable);
			env = env->next;
		}
	}
	while(av[i])
	{
		plus = ft_strrchr_env(av[i], '+');
		if(plus)
			var = ft_substr(av[i], 0, check_equal(av[i]) - 1);
		else
			var = ft_substr(av[i], 0, check_equal(av[i]));
		cont = ft_substr(av[i], check_equal(av[i]) + 1, (ft_strlen(av[i]) - check_equal(av[i])));
		if (av[i] && !pars_export(av[i]))
			printf("minishell: export: `%s': not a valid identifier\n", av[i]);
		else if (av[i] && check_equal(av[i]) && !plus)
		{
			if (check_env(env, var))
				change_env(&env, var, cont);
			else
				ft_lstadd_back_env(&env, ft_lstnew_env(cont, var, 1));
		}
		else if (av[i] && plus)
		{
			if (check_env(env, var))
				change_env(&env, var, ft_strjoin(print_env(&env, var), cont));
			else
				ft_lstadd_back_env(&env, ft_lstnew_env(cont, var, 1));
		}
		else if(av[i] && !check_equal(av[i]))
		{
			if (check_env(env, av[i]))
				change_env(&env, av[i], cont);
			else
				ft_lstadd_back_env(&env, ft_lstnew_env(NULL, av[i], 0));
		}
		free(var);
		free(cont);
		i++;
	}
}

// void	sig_handle(int i)
// {
	
// 	if (i == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int	builts_in(int ac, char **av, char **env)
{
	char		*path;
	char		*line;
	char		**args_1;
	(void)ac;
	(void)av;
	t_list_env	*enev;

	enev = NULL;
	path = getpath(env);
	grep_env(env, &enev);
	if (!path)
		return (0);
	while (1)
	{
		line = readline(BOLD YELLOW "minishell> " RESET);
		add_history(line);
		if (!line)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		args_1 = ft_split(line, ' ');
		if (!ft_strcmp(args_1[0], "echo") || !ft_strcmp(args_1[0], "ECHO"))
			built_echo(args_1, 1);
		else if (!ft_strcmp(args_1[0], "env") || !ft_strcmp(args_1[0], "ENV"))
			built_env(enev);
		else if (!ft_strcmp(args_1[0], "pwd") || !ft_strcmp(args_1[0], "PWD"))
			built_pwd(&enev);
		else if (!ft_strcmp(args_1[0], "unset") || !ft_strcmp(args_1[0], "UNSET"))
			built_unset(enev, args_1);
		else if (!ft_strcmp(args_1[0], "cd") || !ft_strcmp(args_1[0], "CD"))
			built_cd(enev, args_1);
		else if (!ft_strcmp(args_1[0], "export") || !ft_strcmp(args_1[0], "EXPORT"))
			built_export(enev, args_1);
		int i =0;
		while(args_1[i])
		{
			free( args_1[i]);
			args_1[i] = NULL;
			i++;
		}
		free(args_1);
		free(line);
	}
	return (1);
}
