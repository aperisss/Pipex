/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:48:59 by aperis            #+#    #+#             */
/*   Updated: 2022/05/25 15:32:08 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	int		i;
	int		j;

	int		fd[2];
	int		f1;
	int		f2;

	int		id1;
	int		id2;

	char	*str;
	char	*good_path;
	char	**all_path;
	char	**cmd;
}	t_data;

int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);
int		open_file1(char **av, t_data *data);
int		open_file2(char **av, t_data *data);
int		ft_fork(void);
int		ft_pipe(int fd[2]);
int		ft_dup2(int oldfd, int newfd);
int		found_char(char **av, int k);
void	command_error(t_data *data);
void	verif_access(t_data *data, char *str, int fd);
void	get_path(char **envp, char **av, t_data *data, int k);
void	free_get_path(t_data *data);
void	already_path(t_data *data, char **av, int k);
void	pipex(t_data *data, char **av, char **envp);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	**ft_split(char const *s, char c);

#endif
