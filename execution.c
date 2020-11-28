/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:14:42 by ichejra           #+#    #+#             */
/*   Updated: 2020/11/27 13:47:49 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_cmds *cmds)
{
	int i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "HOME") == 0)
			return ;
		i++;
	}
} 
char  *skip_slash(char *line)
{
	char *path;
	int		i;
	int		l;
	int 	c;
	int		j;

	c = 1;
	l = 0;
	while (line[l])
	{
		if (line[l] == '/')
			c++;
		l++;
	}
	l = l - c + 2;
	path = malloc(sizeof(char *) * (l + 1));
	i = 0;
	j = 0;
	while(line[i])
	{	
		if (line[i] == '/' && line[i + 1] == '/')
		{
			i++ ;
			continue ;
		}
		path[j] = line[i];
		i++;
		j++;
	}
	*path = *path + 1;
	if (path[2] == 92 && path[3] != 92)
	{
		i = 3;
		while (i < j)
		{
			path[i - 1] = path[i];
			if (path[i + 1] == '\0')
			{
				path[i] = '\0';
				break;
			}
			i++;
		}
	}
	/* else
	{
		i = 0;
		c = 0;
		while (path[i])
		{
			if (path[i] == '/')
				c = 0;
			if (path[i] == 92)
			{
				if (c % 2 == 0)
				{
					*path = *path + 1;
					i++;
				}
			}
			if (path[i + 1])
			c++;
		}
	} */
	/* else if (path[2] == 92)
	{
		i = 0;
		c = 0;
		while (path[i] != 92)
		{
			if (c % 2 == 0)
			{
				*path = *path + 1;
				i++;
			}
			c++;
		}
		printf("path1 = |%s|\n", path);
	} */
	printf("PATH = |%s|\n", path);
	return (path);
}

/* char	*get_old_pwd(t_cmds *cmds)
{
	int 	i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "OLDPWD") == 0)
			return (cmds->envir[i] + 7);
		i++;
	}
	return (NULL);
}
void	set_pwd(t_cmds *cmds)
{
	int c;
	int i;
	i = 0;
	c = 0;
	while (cmds->envir[c] != NULL)
		c++;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "PWD") == 0)
			cmds->envir[i] = ft_strjoin("PWD=", cmds->pwd);
		if (ft_strcmp(cmds->env_line[0], "OLDPWD") == 0)
			cmds->envir[i] = ft_strjoin("OLDPWD=", cmds->oldpwd);
		i++;
	}
	//cmds->envir[i] = ft_strjoin("OLDPWD=", cmds->oldpwd);
} */

// char	**set_env(char *var, char *value, char **env)
// {
// 	int		i;
// 	int		found;
// 	char	*name;
// 	char	**envp;
// 	char	**tab;

// 	i = 0;
// 	found = 0;
// 	name = ft_strjoin(var, "=");
// 	envp = add_to_arr(env, value, 0);
// 	while (envp[i])
// 	{
// 		tab = ft_split(envp[i], '=');
// 		if (!ft_strcmp(tab[0], var))
// 		{
// 			found = 1;
// 			free(envp[i]);
// 			envp[i] = ft_strjoin(name, value);
// 			return (envp);
// 		}
// 		found = 0;
// 		i++;
// 	}
// 	if (found == 0)
// 		return (add_to_arr(env, value, 1));
// 	return (env);
// }

void	cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int	i;
	int	ret_old = 1;
	char	*tmp;
	//char **str;
	int ret;
	int c;
	// int j = 0;
	ret = 0;
	i = 0;
	c = 0;
	cmds->cd++;  ///bx n9arnha m3a cd - bax t3tini l oldpwd hoa hadak 
	/* while (cmds->envir[j] != NULL)
		j++; */
	cmds->save_oldpwd = getcwd(NULL, 0);
	cmds->oldpwd = cmds->save_oldpwd;
	cmds->pwd = getcwd(NULL, 0);
	//if (!cmds->oldpwd)
	// 	cmds->envir[j++] = ft_strjoin("OLDPWD1================", cmds->oldpwd);
	get_env(cmds);
	if (list->args[1] == NULL)
	{
		// cmds->oldpwd = cmds->pwd;
		ret = chdir(cmds->env_line[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	/* 	while (cmds->envir[j] != NULL)
		{
			str = ft_split(cmds->envir[j], '=');
			if (ft_strcmp(str[0], "OLDPWD") == 0)
			{
				cmds ->envir[j] = ft_strjoin("OLDPWD=", cmds->oldpwd);
			}
			j++;
		}
		if (cmds->envir[j] == NULL)
		{
		} */
		// cmds->envir[j] = ft_strjoin("OLDPWD=", cmds->oldpwd);
		// cmds->envir[j + 1] = NULL;
		//printf("\n\nOLDPWD==|%s|\n\n", cmds->envir[j]);
	}
	else if (list->args[1][0] == '-')
	{
		cmds->minus++;
		if (cmds->minus == cmds->cd)
			cmds->oldpwd = NULL;
		if ((i = ft_getenv("OLDPWD", cmds->envir)) == -1)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
			return ;
		}
		else
		{
			ret_old = chdir(cmds->envir[i] + 7);
			if (ret_old < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
			// else
			// 	ft_putendl_fd(cmds->oldpwd, 1);
			// cmds->envir[j] = ft_strjoin("OLDPWD=", cmds->oldpwd);
			// cmds->envir[j + 1] = NULL;
			// cmds->oldpwd = cmds->save_oldpwd;
		}
	}
	else if (list->args[1][0] == '~')
	{
		if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		{
			//printf("path = |%s|\n", list->args[1]);
			ret = chdir(cmds->env_line[1]);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
		else if (list->args[1][1] == '/')
		{
			tmp = skip_slash(list->args[1]);
			list->args[1] = ft_strjoin(cmds->env_line[1], tmp + 1);
			//printf("path = |%s|\n", list->args[1]);
			ret = chdir(list->args[1]);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
	}
	else if (list->args[1][0] != '~' && list->args[1][0] != '-' &&
		list->args[1][0] != '/' && list->args[1][0] != 92)
	{
		// if (list->args[1][0] == '/')
		// {
		// 	ft_putstr_fd("minishell: cd: " , 1);
		// 	ft_putstr_fd(list->args[1], 1);
		// 	ft_putstr_fd(" :: No such file or directory", 1);
		// }
		//printf("path = |%s|\n", list->args[1]);
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else if (list->args[1][0] == 92)
	{
		i = 0;
		int c = 0;
		while (list->args[1][i] == 92)
		{
			if (c % 2 != 0)
			{
				list->args[1] = list->args[1] + 1;
				i++;
			}
			c++;
		}
		printf("path = |%s|\n", list->args[1]);
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else
	{
		puts("else\n");
		printf("path = |%s|\n", list->args[1]);
		ft_putendl_fd("No such file or directory", 1);
	}
	cmds->pwd = getcwd(NULL, 0);
	cmds->envir = ft_setenv("PWD", cmds->pwd, cmds->envir);
	cmds->envir = ft_setenv("OLDPWD", cmds->save_oldpwd, cmds->envir);
	if (ret_old == 0)
		ft_putendl_fd(cmds->pwd, 1);
	// if (cmds->pwd)
	// {
	// 	cmds->envir[j] = ft_strjoin("PWD1================", cmds->pwd);
	// 	cmds->envir[j + 1] = NULL; 
	// }	
	//if (oldpwd)
	// //cmds->envir = fgt_set_env("OLDPWD", cmds->pwd, cmds->envir)
	// printf("\n1 cmd->pwd = |%s| <-------->\n", cmds->pwd);

	//printf("cpwd2==|%s|\n", cmds->pwd);
	//if (cmds->rem != 1)
	//cmds->pwd = getcwd(NULL, 0);
	//printf("cpwd3==|%s|\n", cmds->pwd);
	// printf("1 cmd->pwd = |%s| <-------->\n\n", cmds->pwd);
	// cmds->envir = ft_set_env("PWD", cmds->pwd, cmds->envir);
	//set OLDPWD and PWD
	//set_pwd(cmds);
}

void	cmd_env(t_cmds *cmds)
{
	//printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	int	i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		if (ft_strchr(cmds->envir[i], '='))
			ft_putendl_fd(cmds->envir[i], 1);
		i++;
	}
	///////////Ajoute PWD a env//////////////////
	/* cmds->pwd = getcwd(NULL, 0);
	if (cmds->pwd)
	{
		while (cmds->envir[j] != NULL)
		{
			cmds->env_line = ft_split(cmds->envir[j], '=');
			if (ft_strcmp(cmds->env_line[0], "PWD") == 0)
			{
				cmds->envir[j] = ft_strjoin("PWD=", cmds->pwd);
				ft_putendl_fd(cmds->envir[j], 1);
				return ;
			}
			j++;
		}
		if (cmds->envir[j] == NULL)
		{
			cmds->envir[j] = ft_strjoin("PWD=", cmds->pwd);
			ft_putendl_fd(cmds->envir[j], 1);
			cmds->envir[j + 1] = NULL; 
		}
	} */
}

void	cmd_pwd(t_cmds *cmds)
{
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
		ft_putendl_fd(cmds->buff, 1);
}

void	cmd_unset(t_cmd_list *list, t_cmds *cmds)
{
	int j = 0;
	int i = 0;
	int k;
	k = 1;
	while (list->args[k] != NULL)
	{
		while (cmds->envir[j] != NULL)
		{
			cmds->env_line = ft_split(cmds->envir[j], '=');
			if (ft_strcmp(cmds->env_line[0], list->args[k]) == 0)
			{
				i = j;
				while (cmds->envir[i] != NULL)
				{
					cmds->envir[i] = cmds->envir[i + 1];
					//if (cmds->envir[i + 1] == NULL)
					//	break ;
					i++;
				}
				break ;
			}
			j++;
		}
		k++;
	}
}

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}