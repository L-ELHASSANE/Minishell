/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:33:32 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:49:54 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_n_flag(char *s, int *n)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (s[0] == '-' && s[1] == 'n' && (s[2] == 'n' || !s[2]))
	{
		*n = 2;
		n_flag = 1;
		while (s[*n] == 'n')
			*n = *n + 1;
		if (s[*n])
		{
			*n = 0;
			n_flag = 0;
		}
	}
	return (n_flag);
}

void	print_args(char **s, int pos)
{
	if (s[pos])
		ft_putstr_fd(s[pos], 1);
	if (s[pos + 1])
		ft_putchar_fd(' ', 1);
}

int		cmd_echo(t_cmd_list *list)
{
	int	i;
	int	n;
	int	ret;

	ret = 0;
	n = 0;
	i = 1;
	while (list->args[i] && check_n_flag(list->args[i], &n))
		i++;
	while (list->args[i])
	{
		if (list->args[i])
			print_args(list->args, i);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}
