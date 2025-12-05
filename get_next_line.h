/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:27:51 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/05 00:55:11 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef GET_NEX_LINE_H
#  define GET_NEX_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1

typedef struct s_node
{
   char *content;
   struct s_node *next;
} t_node;

 
char	*ft_strdup(const char *s);
int count_line_length(t_node *list);
t_node *new_node(char *content);
void add_node_back(t_node **lst, t_node *new);
void free_list(t_node **list, int type, t_node *newline_node);


#endif