/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:42:13 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/07 13:36:10 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_lst_new_env(char *env_var, char *env_value)
{
	t_env	*element;

	element = NULL;
	element = (t_env *)malloc(sizeof(t_env));
	if (element != NULL)
	{
		element->env_var = env_var;
        element->env_value = env_value;
		element->next = NULL;
	}
	return (element);
}

void	ft_lst_add_back_env(t_env **head_en, t_env *new)
{
    
	t_env	*tmp;

	if (head_en)
	{
		if (*head_en == NULL)
		{
			*head_en = new;
			new = NULL;
		}
		else
		{
			tmp = *head_en;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
			tmp = NULL;
			new = NULL;
		}
	}
}

char *get_env_variable(char *variable)
{
    int i;
    char *env_variable;

    i = 0;
    while (variable[i] && variable[i] != '=')
        i++;
    env_variable = ft_substr(variable, 0, i);
    return (env_variable);
}

char *get_env_value(char *value)
{
    int i;
    char *env_value;

    i = 0;
    while (value[i] && value[i] != '=')
        i++;
    if (!ft_strchr(value, '='))
        return (NULL); 
    env_value = ft_substr(value, i + 1, ft_strlen(value) - i);
    return (env_value);
}

void add_env_element(char *env_var, char *env_value, t_env **head_en)
{
    t_env *new;
    new = ft_lst_new_env(env_var, env_value);
    ft_lst_add_back_env(head_en, new);
}
void print_list_env(t_info *info)
{
    t_env *head_en;

    head_en = info->head_en;
    while (head_en != NULL)
    {
        if (head_en->env_value != NULL)
            printf("%s=%s\n", head_en->env_var, head_en->env_value);
        head_en = head_en->next;
    }
}

int check_is_empty_string_env(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int check_if_env_var_exist(t_env *head_en, char *env_var)
{
    while (head_en)
    {
        if (ft_strcmp(head_en->env_var, env_var) == 0)
            return (1);
        head_en = head_en->next;
    }
    return (0);
}

void remove_env_element(t_env **head_en, char *env_var)
{
    t_env *tmp;
    t_env *prev;

    tmp = *head_en;
    if (tmp != NULL && ft_strcmp(tmp->env_var, env_var) == 0)
    {
        *head_en = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && ft_strcmp(tmp->env_var, env_var) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

void fill_env_list(char **environ, t_env **head_env)
{
    int i;
    char *env_variable;
    char *env_value;

    i = 0;
    while (environ[i])
    {
        env_variable = get_env_variable(environ[i]);
        env_value = get_env_value(environ[i]);
        add_env_element(env_variable, env_value, head_env);
        i++;
    }
}


