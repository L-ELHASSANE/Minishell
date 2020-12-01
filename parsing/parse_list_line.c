/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/01 10:41:16 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int		get_exit_status(t_cmds *cmds)
// {
// 	if (cmds->exit_status == 127)
// 		puts("command not found");
// 	else if (cmds->exit_status == 1)
// 		puts("No such file or directory");
// 	else if (cmds->exit_status == 126)
// 		puts("is a directory");
// 	else if (cmds->exit_status == 130)
// 		puts("CTRL-C");
// 	else if (cmds->exit_status == 131)
// 		puts("CTRL-/");
// 	return (cmds->exit_status);
// }

char	*get_env_val(t_cmds *cmds, char *join_arg)
{
	int		j;
	int		k;
	int		i;

	i = 0;
	j = 0;
	k = 0;
	if (cmds->env_val)
		free(cmds->env_val);
	cmds->env_val = ft_strdup(join_arg + 1);
	while (cmds->envir[j] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[j], '=');
		if (ft_strcmp(cmds->env_line[0], cmds->env_val) == 0)
		{
			k = 1;
			return (cmds->env_line[1]);
		}
		j++;
	}
	if (k == 0)
	{
		if (!ft_strcmp(cmds->join_arg, "$"))
			return (ft_strdup("$"));
		else if (!ft_strcmp(cmds->join_arg, "$?"))
		{
			//get_exit_status(cmds);
			exit(0);
		}
		while (cmds->join_arg[++i])
			if (ft_isalpha(cmds->join_arg[i]))
			 	return (ft_strdup(""));
		return (cmds->join_arg);
	}
	return (NULL);
}

int		b_point(char *arg)
{
	int i;

	i = 0;
	while (arg[++i])
		if (ft_strchr("$\\\"';| ", arg[i]))
			return (i);
	return (i);
}

int		get_q(char	**line_list)
{
	int		i;

	i = -1;
	while ((*line_list)[++i])
	{
		if (ft_strchr("\"'", (*line_list)[i]))
		{
			if ((*line_list)[i] == '\"')
				return (2);
			else if ((*line_list)[i] == '\'')
				return (1);
		}
	}
	return (0);
}

void	parse_list_line(char **line_list, t_cmd_list *list, t_cmds *cmds)
{	
	t_cmd_list	*head;
	int			len;
	int			i;
	int			l;
	char		*tmp;
	char		*tmp1;
	char		tmp2[2];
	char		*arg;

	tmp = NULL;
	tmp1 = NULL;
	i = -1;
	len = ft_strlen(*line_list);
	arg = ft_strdup("");
	while (++i <= len)
	{ 
		if ((*line_list)[i] == '$' && (*line_list)[i - 1] != '\\' && get_q(line_list) != 1)
		{
			l = b_point(*line_list + i);
			cmds->join_arg = ft_substr(*line_list + i, 0, l);
			cmds->env_val = get_env_val(cmds, cmds->join_arg);
			tmp = ft_strjoin(arg, cmds->env_val);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp);
			i += l - 1;
		}
		else
		{
			tmp2[0] = (*line_list)[i];
			tmp2[1] = '\0';
			tmp1 = ft_strjoin(arg, tmp2);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp1);
		}
	}
	*line_list = ft_strdup(arg);
	(arg) ? free(arg) : 0;
	(tmp) ? free(tmp) : 0;
	(tmp1) ? free(tmp1) : 0;
	len = ft_strlen(*line_list);
	head = list_line_cmds(list, *line_list, 1);
	i = -1;
	while (++i <= len)
	{
		if ((*line_list)[i] == ';' || (*line_list)[i] == '\0')
		{
			if ((head->prev && head->prev->end) || !head->prev)
				head->start = 1;
			if (head->prev && !head->start)
				head->end = 1;
			head->end = 1;
			if ((*line_list)[i] == ';')
				break ;
		}
		else if ((*line_list)[i] == '|' && (*line_list)[i - 1] != '\\')
		{
			if (!head->prev || (head->prev && head->prev->end))
				head->start = 1;
			(*line_list)[i] = '\0';
			if (head->next)
			{
				update_list(&head, &head->next, list_line_cmds(NULL, *line_list + i + 1, 1));
				head = head->next;
			}
			else
				add_front(&head, list_line_cmds(NULL, *line_list + i + 1, 1));
		}
		else if ((*line_list)[i] == '<')
			head->redir = '<';
		else if ((*line_list)[i] == '>')
		{
			if ((*line_list)[i + 1] == '>')
			{
				head->redir = 'a';
				i++;
			}
			else
				head->redir = '>';
		}
	}
}