/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:45:21 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/03/06 22:45:23 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_main_end(t_bar p1, int **p)
{
	int	i;

	i = 0;
	close_all_pipes(p, p1.ac - 4);
	while (i++ < p1.ac - 4)
		wait(NULL);
	free_it(p1.ultimate, p1.paths, p, p1.ac - 4);
	return (0);
}

int	pipex_main(t_bar p1, char **env)
{
	int	i;

	i = 0;
	p1.envp = get_envp(env);
	if (p1.envp == NULL)
		return (0);
	p1.ultimate = split_all(p1.ac - 3, p1.av + 2);
	if (p1.ultimate == NULL)
	{
		free_it(NULL, p1.envp, NULL, 0);
		return (0);
	}
	p1.paths = get_paths(p1.ac - 3, p1.ultimate, p1.envp);
	if (p1.paths == NULL)
	{
		free_it(p1.ultimate, p1.paths, NULL, 0);
		free_it(NULL, p1.envp, NULL, 0);
		return (0);
	}
	free_it(NULL, p1.envp, NULL, 0);
	return (pipex_main_helper(p1));
}

int	pipex_main_helper(t_bar p1)
{
	int	*pids;
	int	**p;
	int	i;

	i = fill_pipes(&p, p1.ac - 4, &pids);
	if (i != 0)
		return (0);
	while (i < p1.ac - 3)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			close_and_dup(p, i, p1.ac - 3, pids);
			ends_handler(p1.fd1, p1.fd2, i, p1.ac - 3);
			execve((p1.paths)[i], (p1.ultimate)[i], p1.env);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipex_main_end(p1, p));
}

int	pipex(int ac, char **args, char **env)
{
	t_bar	b1;

	b1.fd1 = open(args[1], O_RDWR);
	if (ft_strcmp(args[1], "here_doc") == 0 && ac == 6)
		return (here_doc_exec(ac, args, env));
	if (b1.fd1 == -1)
	{
		perror(args[1]);
		return (-1);
	}
	b1.fd2 = open(args[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (b1.fd2 == -1)
	{
		perror(args[ac - 1]);
		return (-1);
	}
	b1.ac = ac;
	b1.av = args;
	b1.env = env;
	return (pipex_main(b1, env));
}

int	main(int ac, char **av, char **env)
{
	int	i;

	i = 0;
	if (ac < 5)
		return (0);
	return (pipex(ac, av, env));
}
