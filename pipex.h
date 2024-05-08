/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:33:38 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/03/05 13:33:40 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_bar
{
	int		ac;
	int		fd1;
	int		fd2;
	char	**av;
	char	***ultimate;
	char	**paths;
	char	**envp;
	char	**env;
}			t_bar;

typedef struct s_her
{
	int		fd2;
	int		pid1;
	int		pid2;
	int		p[2];
	int		p1[2];
	int		i;
}			t_her;
int			count_words(char *cmd, char sep);
char		*make_words(char *str, char sep);
char		**ft_split(char *cmd, char sep);
char		*ft_strjoin(char *s1, char *s2);
char		**get_paths(int ac, char ***ultimate, char **envp);
char		*get_path(char **paths, char *cmd);
void		free_it(char ***ultimate, char **paths, int **p, int n);
void		free_it_2(int **p, int n);
char		***split_all(int ac, char **av);
int			close_pipes(int **p, int n, int z);
int			close_and_dup(int **p, int i, int n, int *pids);
int			ends_handler(int fd1, int fd2, int i, int n);
int			close_all_pipes(int **p, int z);
int			fill_pipes(int ***p, int n, int **pids);
int			pipex_main_helper(t_bar p1);
int			pipex_main(t_bar p1, char **env);
int			pipex(int ac, char **args, char **env);
int			here_doc_exec_main(t_bar b1);
int			here_doc_exec(int ac, char **av, char **env);
char		**get_envp(char **env);
int			ft_strlen(char *str);
char		*ft_strdup2(char *s1);
char		*ft_strjoin2(char *s1, char *s2, char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_child1(t_her t1, t_bar b1);
int			ft_child2(t_her t1, t_bar b1);
int			ft_main_pipe(t_her t1, t_bar b1);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strncmp_n(char *str, char *str2);
int			ft_putstr_fd(int fd, char *str);
#endif
