/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:27:51 by oamkhou           #+#    #+#             */
/*   Updated: 2025/12/04 18:54:15 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef GET_NEX_LINE_H
#  define GET_NEX_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 2147483646

typedef struct s_node
{
   char *content;
   struct s_node *next;
} t_node;

 
 char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif