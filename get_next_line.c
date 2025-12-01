/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:27:45 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/01 23:36:20 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void *new_node(void *content)
{
    t_node *new_node;

    new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    // content = malloc(sizeof(content) + 1);
    new_node->content = content;
    new_node->next = NULL;
    return (new_node);
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
    while (tmp)
    {
        if (tmp->next == NULL)
        {
            tmp->next = new;
            return;
        }
        tmp = tmp->next;
    }
}
char *extract_line(t_node *list)
{
    t_node *tmp = list;
    char *line;
    int i = 0;

    while (tmp)
    {
        int j = 0;
        while (tmp->content[j]) // go through each character
        {
            line[i] = tmp->content[j]; // copy char
            i++;

            if (tmp->content[j] == '\n') // STOP CONDITION
            {
                line[i] = '\0'; // null-terminate
                return line;
            }
            j++;
        }
        tmp = tmp->next; // go to next node
    }

    line[i] = '\0'; // EOF without newline
    return line;
}

char *get_next_line(int fd)
{

    static t_node *list;
    t_node *node;
    char *buffer;
    char *line;
    int c;

    c = 0;
    buffer = malloc(12);
    list = new_node(NULL);

    while (1)
    {
        c = read(fd, buffer, 12);
        if (c <= 0)
            break;
    }
    node = new_node(buffer);
    add_node_back(&list, node);

    line = extract_line(list);
    return (line);
}

int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *result = get_next_line(fd);
    printf("%s", result);
    free(result);

    // result = get_next_line(fd);
    // printf("%s",result);
    // free(result);
}