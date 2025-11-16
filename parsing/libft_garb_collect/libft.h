/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:36:35 by monabati          #+#    #+#             */
/*   Updated: 2025/11/08 18:10:58 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

//garbage_collector func
typedef struct s_garbage
{
	void				*value;
	struct s_garbage	*next;
}	t_garbage;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(char c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

//original func that use malloc
char		*ft_itoa(int n);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);

//func uses malloc changed them to use ft_malloc and store the address
//to a garbage_collector to free at the end
char		*ft_itoa_g(int n, t_garbage **garb_coll);
void		*ft_calloc(size_t count, size_t size, t_garbage **garb_coll);
char		*ft_strdup_g(const char *s1, t_garbage **garb_coll);
char		*ft_strjoin_g(char const *s1, char const *s2,
				t_garbage **garb_coll);
char		*ft_substr_g(char const *s, unsigned int start, size_t len,
				t_garbage **garb_coll);
char		*ft_strtrim_g(char const *s1, char const *set,
				t_garbage **garb_coll);
char		**ft_split_g(char const *s, char c, t_garbage **garb_coll);

//creat garbage_collector func
void		*ft_malloc(size_t size, t_garbage **garb_lst);

//clear garbage_collector func
void		garbage_clear(t_garbage **garb_list);

#endif