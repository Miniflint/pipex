/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:20:50 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/19 11:31:24 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# define ACCESS_WRONG_PATH "Wrong access path"

// free struct
typedef struct S_ptrs
{
	int		**fd;
	char	**argv;
	char	**envp;
	char	**path;
	char	**command;
	int		i;
	int		on_exit;
}	t_ptrs;

// commands
void	execve_cmd(int *fdin, int *fdout, char *argv, t_ptrs *ptrs);
char	*get_path(char *envpath[]);
int		**pipe_creator(int amount, t_ptrs *ptrs);

// utils
int		ft_strlen(const char *str);
int		ft_strlen_c(const char *str, char c);
int		ft_strcmp(char *s1, char *s2);
char	*good_path(char	**all_paths, t_ptrs *ptrs);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	**split_path(char *str, char *cmd);
int		ft_strchr(char *str, char c);

// free things
void	close_all_fd(t_ptrs *ptrs);
void	**free_tab_v2(void **double_array);

// errors
void	handle_error(int err, t_ptrs *ptrs);

#endif