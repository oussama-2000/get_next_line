/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:39:30 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/06 19:39:03 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(t_node *list)
{
	t_node	*tmp;
	char	*line;
	int		i;
	int		j;

	tmp = list;
	i = 0;
	if (!list)
		return (NULL);
	line = malloc(count_line_length(list) + 1);
	if (!line)
		return (NULL);
	while (tmp)
	{
		j = 0;
		while (tmp->content[j])
		{
			line[i++] = tmp->content[j];
			if (tmp->content[j++] == '\n')
				return (line[i] = '\0', line);
		}
		tmp = tmp->next;
	}
	return (line[i] = '\0', line);
}

t_node	*find_newline_node(t_node *list, int *index)
{
	int		i;
	t_node	*tmp;

	tmp = list;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '\n')
			{
				*index = i;
				return (tmp);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_list(t_node **list)
{
	t_node	*tmp;
	t_node	*newline_node;
	char	*read_left;
	int		i;

	tmp = *list;
	read_left = NULL;
	i = 0;
	newline_node = find_newline_node(*list, &i);
	if (!newline_node)
	{
		free_list(list, NULL);
		*list = NULL;
		return ;
	}
	if (newline_node->content[i + 1] != '\0')
	{
		read_left = ft_strdup(newline_node->content + i + 1);
		if (!read_left)
			return ;
	}
	free_list(list, newline_node);
	*list = NULL; // to reset the pointer 
	if (read_left)
		list_add_back(list, read_left);
}

int	ft_while(int fd, t_node **list)
{
	char	*buffer;
	int		bytes;

	while (!has_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (-1);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (-1);
		}
		if (bytes == 0)
		{
			free(buffer);
			return (1);
		}
		buffer[bytes] = '\0';
		list_add_back(list, buffer);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_node	*list;
	char			*line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = ft_while(fd, &list);
	if (status == -1)
	{
		free_list(&list, NULL);
		return (NULL);
	}
	line = extract_line(list);
	if (list)
		update_list(&list);
	return (line);
}

