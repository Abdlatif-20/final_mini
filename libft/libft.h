/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:39:27 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/12 23:26:47 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <unistd.h> // use write
# include <stdlib.h>/* use size_t And Malloc */
# include "../include/minishell.h"

// typedef struct s_list
// {
// void			*data;
// struct s_list	*next;
// }				t_list;

// typedef struct s_data
// {
// 	char			*word;
// 	int				type;
// 	struct s_data	*next;
// }					t_data;

/* Prototype The Function */

//----------------- Part 1 -----------------------------------

int		ft_isalpha(int c);
int		ft_isdigit(int c );
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *src, char *to_find, size_t len);
int		ft_strncmp(char *str1, char *str2);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t n, size_t size);
char	*ft_strdup(const char *s);

// --------------------- Part 2 ---------------------------------

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//--------------------- Bonus -----------------------------------

// t_data	*ft_lstnew(char	*content);
// void	ft_lstadd_front(t_data **lst, t_data *new);
// int		ft_lstsize(t_data *lst);
// t_data	*ft_lstlast(t_data *lst);
// void	ft_lstadd_back(t_data **lst, t_data *new);
// // void	ft_lstdelone(t_data *lst, void (*del)(void*));
// void	ft_lstclear(t_data **lst);

#endif
