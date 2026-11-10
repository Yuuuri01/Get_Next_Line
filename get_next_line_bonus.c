/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 17:17:25 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/08 17:17:26 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*handle_one(int fd, char *line)
{
	char	buff[CHUNK + 1];
	char	c;
	int		bytes;
	int		i;

	if (line && ft_strchr(line, '\n'))
		return (line);
	i = 0;
	c = 0;
	bytes = 1;
	while (bytes > 0 && c != '\n')
	{
		bytes = read(fd, &c, 1);
		if (bytes == -1)
			return (free(line), NULL);
		if (bytes == 1)
			buff[i++] = c;
		if (i == CHUNK || c == '\n' || bytes == 0)
		{
			buff[i] = '\0';
			line = ft_strjoin(line, buff);
			i = 0;
		}
	}
	return (line);
}

char	*read_line(char *line, int fd)
{
	char	*buff;
	int		bytes;

	if (line && ft_strchr(line, '\n'))
		return (line);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(line), free(buff), NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			return (free(buff), NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (line);
}

char	*free_node(t_list **head, t_list *node)
{
	t_list	*trav;

	if (*head == node)
		*head = node->next;
	else
	{
		trav = *head;
		while (trav->next && trav->next != node)
			trav = trav->next;
		trav->next = node->next;
	}
	free(node->line);
	free(node);
	return (NULL);
}

t_list	*get_node(t_list **head, int fd)
{
	t_list	*trav;
	t_list	*node;

	trav = *head;
	while (trav && trav->fd != fd)
		trav = trav->next;
	if (trav && trav->fd == fd)
		return (trav);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->line = NULL;
	node->next = *head;
	*head = node;
	return (node);
}

char	*get_next_line(int fd)
{
	t_list			*node;
	static t_list	*head;
	char			*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&head, fd);
	if (!node)
		return (NULL);
	if (BUFFER_SIZE == 1)
		node->line = handle_one(fd, node->line);
	else
		node->line = read_line(node->line, fd);
	if (!node->line || !*node->line)
		return (free_node(&head, node));
	result = solve_line(node->line);
	if (!result)
		return (free_node(&head, node));
	node->line = cut_line(node->line);
	return (result);
}
