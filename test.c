/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:39:30 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/04 18:54:06 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int count_line_length(t_node *list)
{
    t_node *tmp = list;
    int len = 0;

    while (tmp)
    {
        int j = 0;
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

char *extract_line(t_node *list)
{
    t_node *tmp = list;
    char *line;
    int len;
    int i = 0;

    if (!list)
        return NULL;
    
    len = count_line_length(list);
    if (len == 0)
        return NULL;
    
    line = malloc(len + 1);
    if (!line)
        return NULL;
        
    while (tmp)
    {
        int j = 0;
        while (tmp->content[j])
        {
            line[i++] = tmp->content[j];
            if (tmp->content[j] == '\n')
            {
                line[i] = '\0';
                return line;
            }
            j++;
        }
        tmp = tmp->next;
    }
    
    line[i] = '\0';
    return line;
}
void free_list(t_node *list)
{
    t_node *tmp;

    while (list)
    {
        tmp = list;
        list = list->next; // start from the first node that list point to
        free(tmp->content);
        free(tmp);
    }
}
void update_list(t_node **list)
{
    t_node *tmp = *list;
    t_node *newline_node = NULL;
    char *leftover = NULL;
    int i = 0;

    if (!list || !*list)
        return;

    // 1) find the node that contain the \n
    while (tmp)
    {
        i = 0;
        while (tmp->content[i])
        {
            if (tmp->content[i] == '\n')
            {
                newline_node = tmp;
                break;
            }
            i++;
        }
        if (newline_node)
            break;
        tmp = tmp->next;
    }

    // 2) if no newline > whole list was returned > free everything
    if (!newline_node)
    {
        free_list(*list);
        *list = NULL;
        return;
    }

    // 3)check if leftover exits after /n and extract it
    if (newline_node->content[i + 1] != '\0')
    {
        leftover = strdup(newline_node->content + i + 1);
        if (!leftover)
            return;
    }

    // 4) free all nodes that belong to the extracted line
    tmp = *list;
    while (tmp)
    {
        t_node *next = tmp->next;
        free(tmp->content);
        free(tmp);
        if (tmp == newline_node)
            break;
        tmp = next;
    }

    // 5) rebuild list only with leftover (if exists)
    if (leftover)
        *list = new_node(leftover);
    else
        *list = NULL;
}

int has_newline(t_node *list)
{
    t_node *tmp = list;
    
    while (tmp)
    {
        int i = 0;
        while (tmp->content[i])
        {
            if (tmp->content[i] == '\n')
                return 1;
            i++;
        }
        tmp = tmp->next;
    }
    return 0;
}

char *get_next_line(int fd)
{
    static t_node *list = NULL;
    t_node *node;
    char *buffer;
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
        return NULL;

    // Read until we find a newline or reach EOF
    while (!has_newline(list))
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer)
        {
            printf("error from malloc\n");
            return NULL;
        }

        bytes_read = read(fd, buffer, BUFFER_SIZE);

        if (bytes_read < 0)  // Error
        {
            free(buffer);
            free_list(list);
            list = NULL;
            return NULL;
        }
        
        if (bytes_read == 0)  // EOF
        {
            free(buffer);
            break;
        }
        
        buffer[bytes_read] = '\0';
        
        node = new_node(buffer);
        add_node_back(&list, node);
    }

    // Extract the line
    line = extract_line(list);
    
    // Update list to keep only leftover content
    update_list(&list);
    
    return line;
}


int main(void)
{
    int fd = open("file.txt", O_RDONLY);

    char *result;
    
    while((result = get_next_line(fd)))
    {
        printf("%s",result);
        free(result);
    }
    // result = get_next_line(fd);
    // printf("%s",result);
    // result = get_next_line(fd);
    // printf("%s",result);
    // result = get_next_line(fd);
    // printf("%s",result);
    return 0;
}