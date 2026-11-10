/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 17:17:04 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/08 17:17:05 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

# define CHUNK 1024

typedef struct s_list
{
	int				fd;
	char			*line;
	struct s_list	*next;
}					t_list;

char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(char *str, char c);
char				*get_next_line(int fd);
char				*solve_line(char *line);
char				*cut_line(char *str);

#endif
