/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamkhou <oamkhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:27:51 by oamkhou           #+#    #+#             */
/*   Updated: 2025/11/30 14:48:34 by oamkhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef GET_NEX_LINE_H
#  define GET_NEX_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


 typedef struct s_node
 {
    char    *content;
    struct  s_node  *next;
 } t_node;

#endif