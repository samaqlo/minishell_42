/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:24:42 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:24:06 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_env(t_list_env *env, char **envp, int i)
{
	t_list_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->c == 1)
			i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		if (env->c == 1)
		{
			envp[i] = ft_strjoin(env->variable, "=");
			if (env->content)
				envp[i] = ft_strjoin(envp[i], env->content);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*join_args(t_cmd_lines *cmd)
{
	char	*arg;

	arg = ft_strjoin("/", cmd->cmd_line[0]);
	return (arg);
}

void	err_file(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	err_cmd(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*get_binary(char **split, char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (split[i])
	{
		res = ft_strjoin(split[i], str);
		if (access(res, F_OK) == 0)
			break ;
		free(res);
		i++;
	}
	return (res);
}
