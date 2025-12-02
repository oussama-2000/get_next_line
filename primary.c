/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:39:30 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/02 12:25:23 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

// Count total characters until newline or end
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

void clean_written(t_node *list)
{
    int node_index = 0;
    int i = 0;
    t_node *tmp;
    tmp = list;
    
    while(tmp->next)
    {
        
        while(tmp->content && tmp->content[i] != '\n')
        {
            i++;
            printf("i : %d\n",i);
        }       
        node_index++;
        if (tmp->content[i] == '\n')
        {
            break;
        }
        tmp= tmp->next;
    }
    printf("node index :%d\n",node_index);
    printf("new line index :%d\n",i);
}
char *get_next_line(int fd)
{
    static t_node *list;
    t_node *node;
    char *buffer;
    char *line;
    int bytes_read;



    while (1)
    {
        buffer = malloc(12 + 1);
        if (!buffer)
            return NULL;
        
        bytes_read = read(fd, buffer, 12);
        
        // if (bytes_read < 0)  // error
        // {
        //     free(buffer);
        //     clean_written(list);
        //     list = NULL;
        //     return NULL;
        // }
        
        if (bytes_read == 0)  // eof
        {
            free(buffer);
            break;
        }
        
        buffer[bytes_read] = '\0';  //FIX: Null-terminate
        
        node = new_node(buffer);
        add_node_back(&list, node);
        
        // Check if we found newline
        // int i = 0;
        // while (i < bytes_read)
        // {
        //     if (buffer[i] == '\n')
        //     {
        //         line = extract_line(list);
        //         // clean_written(list);
        //         // list = NULL;
        //         return line;
        //     }
        //     i++;
        // }
    }

    // EOF reached - return remaining content
    line = extract_line(list);
    clean_written(list);
    // list = NULL;
    return "";
}


int main(void)
{
    int fd = open("file.txt", O_RDONLY);

    char *result;
    
    // while ((result = get_next_line(fd)))
    // {
    //     printf("Line %d: %s", line_num++, result);
    //     free(result);
    // }
    result = get_next_line(fd);
    printf("%s",result);


}