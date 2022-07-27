/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:03:39 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/19 11:44:13 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	**pipe_creator(int amount, t_ptrs *ptrs)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * (amount - 2));
	if (!fd)
		handle_error(EXIT_FAILURE, ptrs);
	while (i < amount - 3)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			handle_error(EXIT_FAILURE, ptrs);
		if (i)
			if (pipe(fd[i]) == -1)
				handle_error(errno, ptrs);
		i++;
		ptrs->i = i;
	}
	fd[i] = NULL;
	fd[0][0] = open(ptrs->argv[1], O_RDONLY);
	fd[0][1] = open(ptrs->argv[amount - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
