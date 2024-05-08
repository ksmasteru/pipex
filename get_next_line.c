/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:44:17 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/01/14 21:00:05 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	while (str[i])
		i++;
	len = i;
	i = 0;
	res = (char *)malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	clear_nodes(t_node **head)
{
	free((*head)->data);
	free(*head);
	*head = NULL;
}

void	format_head(t_node **head)
{
	int		i;
	t_node	*temp;
	char	*holder;

	if (*head == NULL)
		return ;
	i = 0;
	temp = *head;
	holder = ft_strdup(temp->data);
	while (holder[i])
	{
		if (holder[i] == '\n')
		{
			free(temp->data);
			temp->data = ft_strdup(holder + i + 1);
			break ;
		}
		i++;
	}
	if (holder[i] == '\0' || ((*head)->data)[0] == '\0')
		clear_nodes(head);
	free(holder);
}

char	*get_next_line_helper(int *d, int fd)
{
	static t_node	*head;
	t_node			*prev;
	t_node			*new;
	char			*str;

	str = NULL;
	if (head == NULL)
		head = make_node(fd, d);
	else
		*d = check_for_line(head->data);
	prev = head;
	while (*d > 0)
	{
		new = make_node(fd, d);
		prev->next = new;
		prev = new;
	}
	if (*d <= 0)
		str = make_str(&head);
	free(d);
	return (str);
}

char	*get_next_line(int fd)
{
	int				*d;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	d = (int *)malloc(sizeof(int));
	if (!d)
		return (NULL);
	*d = 60;
	return (get_next_line_helper(d, fd));
}
