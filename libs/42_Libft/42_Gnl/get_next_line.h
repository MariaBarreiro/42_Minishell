/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:59:51 by mda-enca          #+#    #+#             */
/*   Updated: 2025/05/08 15:01:01 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

int			ft_strlen_gnl(char *str);
char		*ft_strchr_gnl(char *vault, char c);
char		*ft_strjoin_gnl(char *line, char *vault);
char		*get_next_line(int fd);

#endif
