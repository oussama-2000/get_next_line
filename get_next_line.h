/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:27:51 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/06 00:13:15 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef GET_NEX_LINE_H
#  define GET_NEX_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 42

typedef struct s_node
{
   char *content;
   struct s_node *next;
} t_node;

 
char	*ft_strdup(const char *s);
int count_line_length(t_node *list);
// t_node *new_node(char *content);
// void add_node_back(t_node **lst, t_node *new);
void free_list(t_node **list, t_node *newline_node);
void	list_add_back(t_node **lst, char *content);
int	has_newline(t_node *list);

#endif