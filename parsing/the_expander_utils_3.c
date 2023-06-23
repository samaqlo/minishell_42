/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:42:05 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:21:54 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_value(char *var, t_list_env *env)
{
	char	*tmp;
	char	*str;

	tmp = ft_strdup(var + 1);
	if (!ft_strcmp(tmp, "?"))
	{
		free(tmp);
		tmp = ft_itoa(g_global->exit_status);
		return (tmp);
	}
	while (env)
	{
		str = ft_substr(env->variable, 0, ft_strlen(env->variable));
		if (!ft_strncmp(tmp, "$", ft_strlen(tmp)))
			return (free(str), free(tmp), ft_strdup(""));
		else if (!ft_strcmp(tmp, str))
			return (free(str), free(tmp), expand(env));
		env = env->next;
		free(str);
	}
	return (free(tmp), ft_strdup(""));
}

int	white_sp_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i])
	{
		if (!ft_strchr(" \t\n\v\f\r", str[*i]))
			break ;
		len++;
		(*i)++;
	}
	return (len);
}

int	dollar_len(char *str, int *i)
{
	int	len;

	len = 0;
	len++;
	(*i)++;
	while (str[*i])
	{
		if (str[*i - 1] == '$' && ft_isdigit(str[*i]))
			return ((*i)++, 2);
		if (str[*i - 1] == '$' && str[*i] == '$')
			return ((*i)++, 2);
		else if (!ft_isalnum(str[*i]) && str[*i] != '_')
			break ;
		(*i)++;
		len++;
	}
	return (len);
}

int	len_of_word(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i])
	{
		if (ft_strchr(" \t\n\v\f\r$", str[*i]))
			return (len);
		(*i)++;
		len++;
	}
	return (len);
}

void	fill_vars2(t_data *cmd_line, char *tmp, int j, t_data *head)
{
	if (!ft_strcmp(tmp, "$"))
	{
		if ((cmd_line->next && cmd_line->next->type == space)
			|| !cmd_line->next)
			cmd_line->vars[j] = ft_strdup(tmp);
		else
			cmd_line->vars[j] = set_value(tmp, cmd_line->infos->env);
	}
	else if (dollar_in(tmp) && (cmd_line->type == word
			|| cmd_line->type == dq_word) && !check_prev(head,
			cmd_line->id))
	{
		cmd_line->exp = 1;
		if (cmd_line->type == word)
				cmd_line->vars[j] = skip_space(set_value(tmp,
						cmd_line->infos->env));
		else
			cmd_line->vars[j] = set_value(tmp, cmd_line->infos->env);
	}
	else
		cmd_line->vars[j] = ft_strdup(tmp);
	free(tmp);
}
