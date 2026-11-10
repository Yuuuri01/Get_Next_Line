/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamossai <hamossai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 13:58:19 by hamossai          #+#    #+#             */
/*   Updated: 2026/11/05 13:58:21 by hamossai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define CHUNK 1024

# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*cut_solved(char *line);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*free_line(char *s1, char *s2);

#endif
