/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:48:48 by aperis            #+#    #+#             */
/*   Updated: 2022/08/03 17:02:57 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file1(char **av, t_data *data)
{
	data->f1 = open(av[1], O_RDONLY);
	if (data->f1 < 0)
	{
		perror(av[1]);
		return (-1);
	}
	return (0);
}

int	open_file2(char **av, t_data *data)
{
	data->f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->f2 < 0)
	{
		perror(av[1]);
		return (-1);
	}
	return (0);
}

void	child_one(t_data *data, char **av, char **envp)
{
	if (open_file1(av, data) == 0)
	{
		get_path(envp, av, data, 2);
		verif_access(data, av[2], data->f1);
		data->cmd = ft_split(av[2], ' ');
		ft_dup2(data->f1, 0);
		close(data->f1);
		ft_dup2(data->fd[1], 1);
		close(data->fd[1]);
		close(data->fd[0]);
		execve(data->good_path, data->cmd, NULL);
		perror(data->cmd[0]);
	}
	else
	{
		close(data->fd[1]);
		close(data->fd[0]);
	}
}

void	child_two(t_data *data, char **av, char **envp)
{
	if (open_file2(av, data) == 0)
	{
		get_path(envp, av, data, 3);
		verif_access(data, av[3], data->f2);
		data->cmd = ft_split(av[3], ' ');
		ft_dup2(data->f2, 1);
		close(data->f2);
		ft_dup2(data->fd[0], 0);
		close(data->fd[0]);
		close(data->fd[1]);
		execve(data->good_path, data->cmd, NULL);
		perror(data->cmd[0]);
	}
	else
	{
		close(data->fd[1]);
		close(data->fd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	data.id2 = 0;
	if (ac != 5)
		exit(0);
	ft_pipe(data.fd);
	data.id1 = ft_fork();
	if (data.id1)
		data.id2 = ft_fork();
	if (!data.id1)
		child_one(&data, av, envp);
	if (!data.id2 && data.id1)
		child_two(&data, av, envp);
	close(data.fd[0]);
	close(data.fd[1]);
	waitpid(data.id1, NULL, 0);
	waitpid(data.id2, NULL, 0);
}
