/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:32:48 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/03/05 15:13:55 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex.h"

int	here_doc_exec(int ac, char **av, char **env)
{
	t_bar	b1;

	b1.av = av;
	b1.env = env;
	b1.ac = ac;
	b1.envp = get_envp(env);
	if (b1.envp == NULL)
		return (0);
	b1.ultimate = split_all(2, av + 3);
	if (b1.ultimate == NULL)
	{
		free_it(NULL, b1.envp, NULL, 0);
		return (0);
	}
	b1.paths = get_paths(2, b1.ultimate, b1.envp);
	if (b1.paths == NULL)
	{
		free_it(b1.ultimate, b1.paths, NULL, 0);
		free_it(NULL, b1.envp, NULL, 0);
		return (0);
	}
	free_it(NULL, b1.envp, NULL, 0);
	return (here_doc_exec_main(b1));
}

int	here_doc_exec_main(t_bar b1)
{
	t_her	t1;

	b1.fd2 = open(b1.av[5], O_RDWR | O_APPEND | O_CREAT, 0644);
	if ((pipe(t1.p) == -1) || (pipe(t1.p1) == -1) || (b1.fd2 == -1))
	{
		perror("error");
		return (-1);
	}
	t1.pid1 = fork();
	if (t1.pid1 < 0)
	{
		perror("fork");
		return (-1);
	}
	if (t1.pid1 == 0)
		ft_child1(t1, b1);
	else
	{
		t1.pid2 = fork();
		if (t1.pid2 == 0)
			ft_child2(t1, b1);
		return (ft_main_pipe(t1, b1));
	}
	return (0);
}

int	ft_child1(t_her t1, t_bar b1)
{
	close(t1.p1[0]);
	close(t1.p[1]);
	dup2(t1.p[0], 0);
	close(t1.p[0]);
	dup2(t1.p1[1], 1);
	close(t1.p1[1]);
	t1.i = execve(b1.paths[0], b1.ultimate[0], b1.env);
	if (t1.i == -1)
		perror("execve");
	exit(0);
}

int	ft_child2(t_her t1, t_bar b1)
{
	close(t1.p[1]);
	close(t1.p[0]);
	close(t1.p1[1]);
	dup2(t1.p1[0], 0);
	dup2(b1.fd2, 1);
	close(t1.p1[0]);
	t1.i = execve(b1.paths[1], b1.ultimate[1], b1.env);
	if (t1.i == -1)
		perror("execve");
	exit(0);
}

int	ft_main_pipe(t_her t1, t_bar b1)
{
	char	*str;

	close(t1.p1[0]);
	close(t1.p1[1]);
	close(t1.p[0]);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		str = get_next_line(0);
		if (str == NULL)
			return (0);
		if (ft_strncmp_n(str, (b1.av)[2]) == 0)
			break ;
		write(t1.p[1], str, ft_strlen(str));
		free(str);
	}
	close(t1.p[1]);
	wait(NULL);
	wait(NULL);
	free_it(b1.ultimate, b1.paths, NULL, 0);
	return (0);
}
