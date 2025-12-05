/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:39:30 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/05 01:30:18 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *extract_line(t_node *list)
{
    t_node *tmp;
    char *line;
    int len;
    int i;
    int j;

    tmp = list;
    i = 0;
    if (!list)
        return NULL;
    line = malloc(count_line_length(list) + 1);
    if (!line)
        return NULL; 
    while (tmp)
    {
        j = 0;
        while (tmp->content[j])
        {
            line[i++] = tmp->content[j];
            if (tmp->content[j++] == '\n')
                return (line[i] = '\0' ,line);
        }
        tmp = tmp->next;
    }
    return (line[i] = '\0' , line);
}
t_node *find_newline_node(t_node *list, int *index)
{
    int i;
    t_node *tmp;

    tmp = list;
    while (tmp)
    {
        i = 0;
        while (tmp->content[i])
        {
            if (tmp->content[i] == '\n')
            {
                *index = i;
                return tmp;
            }
            i++;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void update_list(t_node **list)
{
    t_node *tmp = *list;
    t_node *newline_node;
    char *read_left = NULL;
    int i = 0;

    if (!list || !*list)
        return;
    // 1) find the node that contain the \n
    newline_node = find_newline_node(*list, &i);
    // 2) if no newline > whole list was returned > free everything
    if (!newline_node)
    {
        free_list(list,1,NULL);
        *list = NULL;
        return;
    }
    // 3)check if read_left exits after /n and extract it
    if (newline_node->content[i + 1] != '\0')
    {
        read_left = ft_strdup(newline_node->content + i + 1);
        if (!read_left)
            return;
    }
    // 4) free all nodes that belong to the extracted line
    free_list(list,0,newline_node);
    // 5) rebuild list only with read_left (if exists)
    *list = read_left ? new_node(read_left) : NULL;
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
    static t_node *list;
    t_node *node;
    char *buffer;
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
        return NULL;
    // read until we find a newline or reach EOF
    while (!has_newline(list))
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer)
            return NULL;
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)  // read error
        {
            free(buffer);
            free_list(&list,1,NULL);
            // list = NULL;
            return (list=NULL,NULL);
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
    // extract the line
    line = extract_line(list);
    // update list to keep only read_left content
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

}