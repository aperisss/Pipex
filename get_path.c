/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:37:59 by aperis            #+#    #+#             */
/*   Updated: 2022/05/25 15:36:33 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	already_path(t_data *data, char **av, int k)
{
	if (access(av[k], X_OK) == 0)
	{
		data->good_path = ft_strdup(av[k]);
		data->j = 1;
	}
	else
	{
		if (found_char(av, k) == 1)
		{
			if (access(av[k], X_OK) == 0)
				data->good_path = ft_strdup(av[k]);
			else
				perror(av[k]);
		}
	}	
}

void	free_get_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->all_path[i])
	{
		free(data->all_path[i]);
		i++;
	}
	i = 0;
	while (data->cmd[i])
	{
		free(data->cmd[i]);
		i++;
	}
	free(data->cmd);
	free(data->all_path);
}

void	verif_access(t_data *data, char *str, int file)
{
	if (access(data->good_path, X_OK) != 0)
	{
		write(1, str, ft_strlen(str));
		write(1, " : Command not found\n", 21);
		close(file);
		close(data->fd[0]);
		close(data->fd[1]);
		free(data->good_path);
		exit(0);
	}
}

void	no_path(t_data *data)
{
	if (data->j == 0)
		data->good_path = ft_strdup(data->all_path[0]);
}

void	get_path(char **envp, char **av, t_data *data, int k)
{
	data->i = 0;
	data->j = 0;
	while (envp[data->i])
	{
		if (ft_strncmp(envp[data->i], "PATH=", 5) == 0)
			data->str = envp[data->i];
		data->i++;
	}
	data->i = 0;
	data->all_path = ft_split(data->str + 5, ':');
	data->cmd = ft_split(av[k], ' ');
	already_path(data, av, k);
	while (data->all_path[data->i] && data->j == 0)
	{
		data->all_path[data->i]
			= ft_strjoin2(data->all_path[data->i], data->cmd[0]);
		if (access(data->all_path[data->i], X_OK) == 0)
		{
			data->good_path = ft_strdup(data->all_path[data->i]);
			data->j = 1;
		}
		data->i++;
	}
	no_path(data);
	free_get_path(data);
}
