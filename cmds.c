/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:17:45 by elahyani          #+#    #+#             */
/*   Updated: 2020/10/30 18:35:12 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_cmds *cmds)
{
	int	i;
	
	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "HOME") == 0)
			return ;
		i++;
	}
}

void	cmd_cd(t_cmds *cmds)
{
	int	i;

	i = 0;
	get_env(cmds);
	if (cmds->cmd[1] == NULL)
	{
		chdir(cmds->env_line[1]);
		return;
	}
	if (cmds->cmd[1][0] != '~')
		chdir(cmds->cmd[cmds->counter]);
	else if (cmds->cmd[1][0] == '~')
	{
		cmds->cmd[1] = ft_strjoin(cmds->env_line[1], cmds->cmd[1] + 1);
		chdir(cmds->cmd[cmds->counter]);
	}
}

void	cmd_echo(t_cmds *cmds)
{
	int	i;
	
	i = 1;
	while (i <= cmds->counter)
	{
		ft_putstr_fd(cmds->cmd[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	cmd_pwd()
{
	char	*buff;

	if ((buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
		ft_putendl_fd(buff, 1);
}

void	cmd_env(t_cmds *cmds)
{
	int	i;
	
	i = 0;
	while (cmds->envir[i] != NULL)
	{
		ft_putendl_fd(cmds->envir[i], 1);
		i++;
	}
}

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}