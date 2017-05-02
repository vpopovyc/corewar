/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:48:30 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/03/23 18:44:29 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <locale.h>
# include <wchar.h>
# include <wctype.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "ft_fprintf.h"
# define M_PI_180 0.01745329251994
# define BS 8
# define BUFF_SIZE 65000

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big,
		const char *little, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_issign(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
long				ft_do_op(char *n1, char *n2, char c);
void				ft_intzero(int ar[], int f, size_t n);
char				*ft_realloc(char *arr_in, size_t len);
char				*ft_strnfjoin(char *s1, char *s2, size_t n);
size_t				ft_atosize_t(char *s);
int					ft_isprintf_spec(int c);
int					ft_isprintf_up_spec(int c);
char				*ft_sstoab(ssize_t value, ssize_t base);
char				*ft_stoab(size_t value, size_t base);
int					ft_iscl_group1(char c);
int					ft_iscl_group2(char c);
int					ft_iscl_group3(char c);
void				ft_capitalize(char *s);
void				ft_loweralize(char *s);
void				ft_psn(char *s, unsigned int n);
void				ft_pssn(char s, unsigned int n);
size_t				ft_wstrlen(wchar_t *s);
char				ft_wstrblen(wchar_t c);
char				*ft_uct8(wchar_t c, unsigned char *data, char n);
void				ft_pspp(char **s);
size_t				ft_wstrmem(wchar_t *s);
void				ft_ppdel(char ***sv);
char				*ft_strndup(char *sv, size_t n);
ssize_t				ft_power(ssize_t x, ssize_t n);
void				ft_charstc(char s[], int n, const char *sv);
int					ft_atoi_base(char *sv, int bs);
int					ft_ishex(char c);
size_t				ft_chexlen(char *sv);
void				pspp(char **s, int fd);
void				pssn(char s, unsigned int n, int fd);
void				psn(char *s, unsigned int n, int fd);
size_t				ft_strclen(char *sv, char c);
#endif
