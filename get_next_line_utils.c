/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:46:39 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/01/14 20:23:45 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_len(t_node *head)
{
	int		i;
	int		j;
	t_node	*temp;
	char	*holder;

	temp = head;
	i = 0;
	while (temp)
	{
		holder = temp->data;
		j = 0;
		while (holder[j])
		{
			if (holder[j] == '\n')
				return (i + 1);
			j++;
			i++;
		}
		temp = temp->next;
	}
	return (i);
}

int	check_for_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (-2);
		i++;
	}
	return (1);
}

t_node	*make_node(int fd, int *d)
{
	t_node	*new;
	char	*holder;
	int		s;

	s = 0;
	holder = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	new = malloc(sizeof(t_node));
	if (!holder || !new)
		return (NULL);
	holder[BUFFER_SIZE] = '\0';
	s = read(fd, holder, BUFFER_SIZE);
	if (s == 0 || s == -1)
	{
		*d = s;
		free(holder);
		free(new);
		return (NULL);
	}
	holder[s] = '\0';
	new->data = ft_strdup(holder);
	*d = check_for_line(holder);
	free(holder);
	new->next = NULL;
	return (new);
}

void	make_str_final(t_node **head, t_node *nachste, char *str, int j)
{
	t_node	*temp;

	temp = *head;
	while (temp)
	{
		nachste = temp->next;
		j = 0;
		while ((temp->data)[j] != '\0')
		{
			if ((temp->data)[j] == '\n')
			{
				*(str) = (temp->data)[j];
				*head = temp;
				return ;
			}
			*(str++) = (temp->data)[j++];
		}
		if (temp->next == NULL)
		{
			*head = temp;
			return ;
		}
		clear_nodes(&temp);
		temp = nachste;
	}
}

char	*make_str(t_node **head)
{
	t_node	*nachste;
	int		i;
	int		j;
	int		len;
	char	*str;

	nachste = NULL;
	if (*head == NULL)
		return (NULL);
	len = str_len(*head);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	make_str_final(head, nachste, str, 0);
	format_head(head);
	return (str);
}
