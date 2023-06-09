/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:37:52 by astalha           #+#    #+#             */
/*   Updated: 2023/06/09 14:47:52 by astalha          ###   ########.fr       */
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
	ft_lstadd_back_env(enev, ft_lstnew_env("0", "?", 1));
}

int	check_n(char *av)
{
	int	i;

	i = 1;
	if(av[0] && av[0] != '-')
		return 1;
	while (av[i])
	{
		if (av[i] != 'n')
			return 1;
		i++;
	}
	return (0);
}

void	built_echo(char **av)
{
	int	i;
	int	test;

	i = 1;
	test = 1;
	
	while (av[i])
	{
		if  (!check_n(av[i]))
		{
			test = 0;
			i++;
		}
		printf("%s", av[i++]);
		if (!av[i + 1])
			printf(" ");	
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
	
	change_env(&env, "OLDPWD", print_env(&env, "PWD"));
	if (!args[1])
	{
		if (!print_env(&env, "HOME"))
		{
			printf("cd: HOME not set\n");
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

int	builts_in(t_cmd_lines *cmd, t_list_env **enev)
{
	if (!ft_strcmp(cmd->cmd_line[0], "echo") || !ft_strcmp(cmd->cmd_line[0], "ECHO"))
		built_echo(cmd->cmd_line);
	else if (!ft_strcmp(cmd->cmd_line[0], "env") || !ft_strcmp(cmd->cmd_line[0], "ENV"))
		built_env(*enev);
	else if (!ft_strcmp(cmd->cmd_line[0], "pwd") || !ft_strcmp(cmd->cmd_line[0], "PWD"))
		built_pwd(enev);
	else if (!ft_strcmp(cmd->cmd_line[0], "unset") || !ft_strcmp(cmd->cmd_line[0], "UNSET"))
		built_unset(*enev, cmd->cmd_line);
	else if (!ft_strcmp(cmd->cmd_line[0], "cd") || !ft_strcmp(cmd->cmd_line[0], "CD"))
		built_cd(*enev, cmd->cmd_line);
	else if (!ft_strcmp(cmd->cmd_line[0], "export") || !ft_strcmp(cmd->cmd_line[0], "EXPORT"))
		built_export(*enev, cmd->cmd_line);
	int i =0;
	puts("done");
	while(cmd->cmd_line[i])
	{
		free( cmd->cmd_line[i]);
		cmd->cmd_line[i] = NULL;
		i++;
	}
	free(cmd->cmd_line);
	return (1);
}
