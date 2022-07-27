/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:30:09 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/19 11:31:31 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_all(int **fd, int i)
{
	if (i)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	else
		close(fd[0][0]);
}

void	handle_pipes(t_ptrs *ptr, int argc)
{
	int		i;
	int		id;

	i = 0;
	while (i < argc - 3)
	{
		if (ptr->on_exit == 1)
			handle_error(EXIT_FAILURE, ptr);
		id = fork();
		if (id == -1)
			handle_error(errno, ptr);
		if (id == 0)
			execve_cmd(ptr->fd[i], ptr->fd[i + 1], ptr->argv[i + 2], ptr);
		else
		{
			close_all(ptr->fd, i);
			if (++i == argc - 4)
				execve_cmd(ptr->fd[i], ptr->fd[0], ptr->argv[argc - 2], ptr);
		}
	}
}

void	set_ptrs(t_ptrs *ptrs)
{
	ptrs->i = 0;
	ptrs->on_exit = 0;
	ptrs->command = NULL;
	ptrs->path = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		first_file;
	t_ptrs	ptrs;

	if (argc <= 4)
	{
		write(1, "pipex: Not enough arguments\n \
				Usage: ./pipex infile1 cmd1 cmd2 outfile2", 71);
		exit(EXIT_FAILURE);
	}
	set_ptrs(&ptrs);
	ptrs.envp = envp;
	ptrs.argv = argv;
	ptrs.fd = pipe_creator(argc, &ptrs);
	if (!ptrs.fd)
		handle_error(errno, &ptrs);
	first_file = open(argv[1], O_RDONLY);
	if (first_file == -1)
		handle_error(errno, &ptrs);
	else
		close(first_file);
	handle_pipes(&ptrs, argc);
	return (0);
}
