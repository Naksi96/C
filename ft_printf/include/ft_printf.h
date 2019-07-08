/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:00:07 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 18:29:34 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define ERR_CHECK(x)   if (!x) return (NULL)

typedef struct		s_flag
{
	int				negative;
	int				positive;
	int				space;
	int				hash;
	int				zero;
}					t_flag;

typedef struct		s_param
{
	char			*str;
	char			type;
	t_flag			flag;
	int				width;
	int				precision;
	int				length;
	int				pos;
	int				nulcheck;
	int				checkzz;
	int				neg;
	int				special;
}					t_param;

typedef char		*(*t_func)(t_param*, va_list);

void				ft_putchar(char c);
void				ft_putnbr(int n);
void				ft_putstr(const char *s);
int					ft_printf(char *format, ...);
int					print_param(t_param *arg, va_list ap);
int					ft_atoi(const char *str);
char				*ft_dtoa(long double d, t_param *arg);
char				*ft_itoa(unsigned long long n, unsigned int base);
void				ft_tolower(char *str);
unsigned long long	ft_power(int nbr, int n);
int					ft_iswhitespace(char c);
int					ft_isdigit(int c);
int					ft_countdigit(unsigned long long nbr, unsigned int base);
int					ft_isupper(int c);
int					ft_isalpha(int c);
int					ft_checknegative(long long n);
void				count_dec(long double *dec, int *count);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, int n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					dup_check(char *str, char c);
void				*ft_memalloc(size_t size);
void				ft_bzero(void *s, size_t n);
char				*ft_strnew(size_t size);
void				ft_memdel(void **ap);
void				*ft_memset(void *b, int c, size_t len);
char				*print_d_i(t_param *arg, va_list ap);
char				*print_c(t_param *arg, va_list ap);
char				*print_s(t_param *arg, va_list ap);
char				*print_p(t_param *arg, va_list ap);
char				*print_f_e(t_param *arg, va_list ap);
void				param_reset(t_param *arg);
t_param				*new_param(char *format);
t_func				set_function(char c);
void				check_flag(t_param *arg);
void				check_width(t_param *arg, va_list ap);
void				check_precision(t_param *arg, va_list ap);
void				check_size(t_param *arg);
void				check_conversion(t_param *arg, va_list ap);
char				*handle_all(t_param *arg, va_list ap);
char				*handle_precision(char *str, t_param *arg);
char				*handle_flag(char *str, t_param *arg);
char				*get_sign(t_param *arg);
char				*get_hash(t_param *arg, char *str);
int					check_base(t_param *arg);
char				*fill_zerochar(int decpos);
char				*ft_wstrdup(wchar_t *wchar);
size_t				w_strlen(unsigned *str);

#endif
