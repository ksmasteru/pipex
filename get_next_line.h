/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:01:38 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/01/14 20:56:36 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 14
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}					t_node;
char				*final_str(t_node **head, t_node *temp, char *str, int j);
char				*ft_strdup(char *str);
int					str_len(t_node *head);
void				make_str_final(t_node **head, t_node *nachste, char *str,
						int j);
int					check_for_line(char *buffer);
t_node				*make_node(int fd, int *d);
char				*make_str(t_node **head);
char				*get_next_line_helper(int *d, int fd);
void				format_head(t_node **head);
char				*get_next_line(int fd);
void				clear_nodes(t_node **head);
#endif
