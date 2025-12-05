/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 01:24:28 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/05 01:27:06 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strdup(const char *s)
{
	char *str;
	size_t size;
	size_t i;
	int len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	if (!s)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
int count_line_length(t_node *list)
{
	t_node *tmp;
	int len;
	int j;

	tmp = list;
	len = 0;
	while (tmp)
	{
		j = 0;
		while (tmp->content[j])
		{
			len++;
			if (tmp->content[j] == '\n')
				return len;
			j++;
		}
		tmp = tmp->next;
	}
	return len;
}
t_node *new_node(char *content)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return node;
}
void add_node_back(t_node **lst, t_node *new)
{
	t_node *tmp;

	if (!lst || !new)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
// if type == 1 means whole list ;type == 0 just nodes
void free_list(t_node **list, int type, t_node *newline_node)
{
	t_node *tmp;
	t_node *next;

	if (!list || !*list)
		return;
	tmp = *list;
	// free everything
	if (type == 1)
	{
		while (tmp)
		{
			next = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = next;
		}
		*list = NULL;
		return;
	}
	// free until newline_node (included)
	while (tmp)
	{
		next = tmp->next;
		free(tmp->content);
		free(tmp);
		if (tmp == newline_node)
			break;
		tmp = next;
	}
	// update list start (next node after newline)
	*list = next;
}
