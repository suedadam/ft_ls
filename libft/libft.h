/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:27:49 by asyed             #+#    #+#             */
/*   Updated: 2017/11/30 14:35:40 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# define TRIMSPACE(c) (c == ' ' || c == '\n' || c == '\t')

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
int				ft_isspace(int	c);
int				ft_isupper(int c);
char			*ft_itoa(int n);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *ptr, int val, size_t num);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(__int64_t n);
void			ft_putnbr_fd(__int64_t n, int fd);
void			ft_uputnbr(__uint64_t n);
void			ft_uputnbr_fd(__uint64_t n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
void			ft_strdel(char **ap);
char			*ft_strdup(const char *s);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *dest, const char *src, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_strnequ(char const *s1, char const *s2, size_t len);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *in, const char *str, size_t n);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *in, const char *str);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*ft_realloc(void *src, size_t new_size);
size_t			ft_wcslen(const wchar_t *s);
size_t			ft_nbrlen(intmax_t n);

#endif
