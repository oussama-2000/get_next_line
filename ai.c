/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:39:30 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/02 22:52:57 by oamkhou          ###   ########.fr       */
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

void free_list(t_node *list)
{
    t_node *tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->content);
        free(tmp);
    }
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

// Free nodes and update list to keep only leftover after newline
void update_list(t_node **list)
{
    t_node *tmp;
    t_node *last_node;
    char *leftover;
    int i;

    if (!list || !*list)
        return;

    tmp = *list;
    last_node = NULL;
    
    // Find the node containing '\n'
    while (tmp)
    {
        i = 0;
        while (tmp->content[i])
        {
            if (tmp->content[i] == '\n')
            {
                // Found newline - save leftover content
                if (tmp->content[i + 1] != '\0')
                {
                    // There's content after newline
                    leftover = malloc(strlen(tmp->content + i + 1) + 1);
                    if (!leftover)
                        return;
                    
                    int j = 0;
                    i++; // Skip the newline
                    while (tmp->content[i])
                        leftover[j++] = tmp->content[i++];
                    leftover[j] = '\0';
                    
                    // Free all nodes
                    free_list(*list);
                    
                    // Create new list with leftover
                    *list = new_node(leftover);
                    return;
                }
                else
                {
                    // Newline is at end of buffer - free everything
                    free_list(*list);
                    *list = NULL;
                    return;
                }
            }
            i++;
        }
        tmp = tmp->next;
    }
    
    // No newline found - this means EOF was reached
    // Free everything since we returned all content
    free_list(*list);
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

    if (fd < 0 || 12 <= 0)
        return NULL;

    // Read until we find a newline or reach EOF
    while (!has_newline(list))
    {
        buffer = malloc(12 + 1);
        if (!buffer)
            return NULL;
        
        bytes_read = read(fd, buffer, 12);
        
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

/* TEST MAIN */
int main(void)
{
    int fd = open("file.txt", O_RDONLY);

    char *result;
    
    result = get_next_line(fd);
    printf("%s",result);
    result = get_next_line(fd);
    printf("%s",result);
    result = get_next_line(fd);
    printf("%s",result);
    return 0;
}