/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 01:24:28 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/06 19:38:18 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char *ft_strdup(const char *s)
{
    char *str;
    int i;
    int len;

    len = 0;
    if (!s)
        return (NULL);
    while (s[len] != '\0')
    {
        len++;
    }
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
                return (len);
            j++;
        }
        tmp = tmp->next;
    }
    return (len);
}

void list_add_back(t_node **lst, char *content)
{
    t_node *node;
    t_node *tmp;

    if (!lst || !content)
        return;
    node = malloc(sizeof(t_node));
    if (!node)
        return;
    node->content = content;
    node->next = NULL;
    if (!*lst)
    {
        *lst = node;
        return; // create node and out
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void free_list(t_node **list, t_node *newline_node)
{
    t_node *tmp;
    t_node *next;

    if (!list || !*list)
        return;
    tmp = *list;
    while (tmp)
    {
        next = tmp->next;
        free(tmp->content);
        free(tmp);
        if (tmp == newline_node)
            break;
        tmp = next;
    }
    *list = next;
}

int has_newline(t_node *list)
{
    t_node *tmp;
    int i;

    tmp = list;
    while (tmp)
    {
        i = 0;
        while (tmp->content[i])
        {
            if (tmp->content[i] == '\n')
                return (1);
            i++;
        }
        tmp = tmp->next;
    }
    return (0);
}
