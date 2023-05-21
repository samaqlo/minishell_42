/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:37:52 by astalha           #+#    #+#             */
/*   Updated: 2023/05/22 00:13:45 by astalha          ###   ########.fr       */
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

t_list_env	*ft_lstnew_env(char *content, char *variable)
{
	t_list_env	*new;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (!new)
		return (NULL);
	new->variable = ft_strdup(variable);
	new->content = ft_strdup(content);
	new->c = 1;
	new->next = NULL;
	return (new);
}

int	check_equal(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (i);
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
		variable = ft_substr(env[i], 0, len_eq + 1);
		content = ft_substr(env[i], len_eq + 1, ft_strlen(env[i]) - len_eq);
		ft_lstadd_back_env(enev, ft_lstnew_env(content, variable));
		i++;
		free(variable);
		free(content);
	}
}

int	check_n(char *av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	built_echo(char **av)
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
		printf("%s ", av[i++]);
	}
	if (test == 1)
		printf("\n");
}

char	*built_pwd(void)
{
	char	str[1024];

	if (getcwd(str, sizeof(str)))
		printf("%s\n", str);
	else
		printf("\n");
	return (ft_strdup(str));
}

char	*getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
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
			printf("%s\n", enev->content);
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
						ft_strlen(enev->variable) - 1)))
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
			tmp->content = ft_strdup(cont);
		}
		tmp = tmp->next;
	}
}
char	*print_env(t_list_env **env, char *var)
{
	t_list_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var) && tmp->content)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	built_cd(t_list_env *env, char **args)
{
	char	str[1024];

	change_env(&env, "OLDPWD=", getcwd(str, sizeof(str)));
	if (!args[1])
	{
		if (print_env(&env, "HOME="))
		{
			printf("cd: HOME not set\n");
			return ;
		}
		chdir(print_env(&env, "HOME="));
		change_env(&env, "PWD=", getcwd(str, sizeof(str)));
	}
	else if (access(args[1], F_OK) == -1)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (access(args[1], R_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (access(args[1], X_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (args[1] && !ft_strcmp(args[1], ".."))
	{
		chdir(ft_strrchr_env(str, '/'));
		change_env(&env, "PWD=", getcwd(str, sizeof(str)));
	}
	else if (args[1])
	{
		chdir(args[1]);
		change_env(&env, "PWD=", getcwd(str, sizeof(str)));
	}
}

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
			continue ;
		args_1 = ft_split(line, ' ');
		if (!(strcmp(args_1[0], "echo")))
			built_echo(args_1);
		else if (!(strcmp(args_1[0], "env")))
			built_env(enev);
		else if (!(strcmp(args_1[0], "pwd")))
			built_pwd();
		else if (!(strcmp(args_1[0], "unset")))
			built_unset(enev, args_1);
		else if (!(strcmp(args_1[0], "cd")))
			built_cd(enev, args_1);
	}
	return (1);
}
