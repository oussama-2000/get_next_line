/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:27:51 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/06 21:19:42 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef GET_NEX_LINE_BONUS_H
#define GET_NEX_LINE_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>




typedef struct s_node
{
    char *content;
    struct s_node *next;
} t_node;

char *get_next_line(int fd);
int ft_while(int fd, t_node **list);
void update_list(t_node **list);
t_node *find_newline_node(t_node *list, int *index);
char *extract_line(t_node *list);
char *ft_strdup(const char *s);
int count_line_length(t_node *list);
void free_list(t_node **list, t_node *newline_node);
void list_add_back(t_node **lst, char *content);
int has_newline(t_node *list);

#endif
