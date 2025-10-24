/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:24:26 by mda-enca          #+#    #+#             */
/*   Updated: 2025/05/08 16:24:32 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1
# endif

# ifndef MAX_FD_SIZE 
#  define MAX_FD_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

int			ft_strlen_gnl(char *str);
char		*ft_strchr_gnl(char *vault, char c);
char		*ft_strjoin_gnl(char *line, char *vault);
char		*get_next_line(int fd);

#endif
