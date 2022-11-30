/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:31:23 by aperis            #+#    #+#             */
/*   Updated: 2022/05/25 15:46:36 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fork(void)
{
	int	tmp;

	tmp = fork();
	if (tmp == -1)
	{
		perror("fork");
		exit(0);
	}
	return (tmp);
}

int	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(0);
	}
	return (1);
}

int	ft_dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (1);
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(0);
	}
	close(oldfd);
	return (1);
}

int	found_char(char **av, int k)
{
	int	i;

	i = 0;
	while (av[k][i])
	{
		if (av[k][i] == '/')
			return (1);
		i++;
	}
	return (0);
}
