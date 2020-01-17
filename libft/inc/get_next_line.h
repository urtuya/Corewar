/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 20:42:41 by vellery-          #+#    #+#             */
/*   Updated: 2019/10/23 18:42:27 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef GET_NEXT_LINE_H
// # define GET_NEXT_LINE_H

// # include "libft.h"
// # include <string.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <fcntl.h>

// # define BUFF_SIZE 500
// # define CHECK(x) if (!x) return (-1);

// int get_next_line (const int fd, char **line);

// #endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 500

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int	get_next_line(int fd, char **line);

#endif
