/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_str.h                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:07:35 by adandres               /    /  /         */
/*   Updated: 2020/05/26 22:41:38 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_STR_H
# define MY_STR_H

# include <stdlib.h>

char			*my_strnew(size_t size);
char			*my_strsub(char const *s, unsigned int start, size_t len);
int			my_strnequ(char const *s1, char const *s2, size_t n);
int			my_strequ(char const *s1, char const *s2);
char			*my_strmapi(char const *s, char (*f)(unsigned int, char));
char			*my_strmap(char const *s, char (*f)(char));
void			my_striteri(char *s, void (*f)(unsigned int, char *));
void			my_striter(char *s, void (*f)(char *));
int			my_strncmp(const char *s1, const char *s2, size_t n);
int			my_strcmp(const char *s1, const char *s2);
char			*my_strnstr(const char *str, const char *to_find, size_t len);
char			*my_strstr(const char *str, const char *to_find);
char			*my_strrchr(const char *s, int c);
char			*my_strchr(const char *s, int c);
size_t			my_strlcat(char *dest, const char *src, size_t size);
char			*my_strncat(char *dest, const char *src, size_t nb);
char			*my_strcat(char *dest, const char *src);
char			*my_strncpy(char *dest, const char *src, size_t len);
char			*my_strcpy(char *dest, const char *src);
char			*my_strdup(const char *s1);
size_t			my_strlen(const char *s);
char			*my_strjoin(const char *s1, const char *s2);
char			*my_strtoupper(char *str);
char			*my_strtolower(char *str);
void			my_strclr(char *str);
char			*my_strndup(const char *s1, int n);
char			*my_strjoin_free(char *s1, char *s2);
char			**my_strsplit(const char *str, char c);
int			my_strichr(char *str, char to_find);
char			*my_strjoin_tab(char **tab, char *del);
char			*my_strcdel(char *str, int i);
int			my_strcount(char *str, char c);

#endif
