/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:24:49 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/26 15:03:35 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SOLONG 
# define LIBFT_SOLONG

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>

char	*ft_strrchr(const char *s, int c);

/* ft_printf */

void	ft_format_and_count(char s, va_list ap, size_t *count);
size_t	ftpr_putchar(char c);
size_t	ftpr_puthex(size_t h, char c);
size_t	ftpr_putint(int n);
size_t	ftpr_putstr(char *s);
size_t	ftpr_putptr(size_t p);
size_t	ftpr_putunsdec(unsigned int d);
int		ft_printf(const char *s, ...);

/* ft_get_next_line */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9 
# endif

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*get_next_line(int fd);
char	*create_result(int i, char *s);
int		ft_extend(char **line, int *l_buf_mul);
int		ft_strlen(const char *str);
void	ft_reset_s(char *s, int j);
char	*ft_write_line(char *s, char *line, int bytes_returned, int j);
int		ft_s_eof_check(char *s, char *line, int bytes_returned);
void	ft_set_to_zero(int *i, int *j, int *k);

#endif
