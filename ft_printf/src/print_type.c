/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:22:36 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 20:03:01 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_proper_func(unsigned long long ldi, long long di, int base)
{
	char	*store_int;

	if (ldi)
		store_int = ft_itoa(ldi, base);
	else if (ft_checknegative(di))
		store_int = ft_itoa(-di, base);
	else if (!(ft_checknegative(di)))
		store_int = ft_itoa(di, base);
	else
		return (NULL);
	return (store_int);
}

static char	*print_d_i_ext2(t_param *arg, va_list ap, int base)
{
	char				*store_int;
	long long			di;
	unsigned long long	ldi;

	ldi = 0;
	di = 0;
	if (arg->length == 4)
	{
		(arg->type == 'd' || arg->type == 'i') ? (di = va_arg(ap, long long))
							: (ldi = va_arg(ap, unsigned long long));
	}
	else if (arg->length == 6)
	{
		(arg->type == 'd' || arg->type == 'i') ? (di = va_arg(ap, intmax_t))
							: (ldi = va_arg(ap, uintmax_t));
	}
	else if (arg->length == 7)
	{
		(arg->type == 'd' || arg->type == 'i') ? (di = va_arg(ap, long long))
							: (ldi = va_arg(ap, size_t));
	}
	store_int = get_proper_func(ldi, di, base);
	arg->neg = (ft_checknegative(di)) ? 1 : 0;
	return (store_int);
}

static char	*print_d_i_ext(t_param *arg, va_list ap, int base)
{
	char				*st_int;
	long long			di;
	unsigned long long	ldi;

	ldi = 0;
	di = 0;
	if (arg->length == 2 && arg->type != 'U')
	{
		(arg->type == 'd' || arg->type == 'i') ? (di = (short)va_arg(ap, int))
							: (di = (unsigned short)va_arg(ap, unsigned int));
		st_int = (ft_checknegative(di)) ? ft_itoa(-di, base)
					: ft_itoa(di, base);
		arg->neg = (ft_checknegative(di)) ? 1 : 0;
	}
	else if (arg->length == 3 || arg->type == 'U')
	{
		(arg->type == 'd' || arg->type == 'i') ? (di = va_arg(ap, long))
							: (ldi = va_arg(ap, unsigned long));
		st_int = get_proper_func(ldi, di, base);
		arg->neg = (ft_checknegative(di)) ? 1 : 0;
	}
	else
		st_int = print_d_i_ext2(arg, ap, base);
	return (st_int);
}

char		*print_d_i(t_param *arg, va_list ap)
{
	char		*st_int;
	long long	digit;

	if (arg->length == 0 && arg->type != 'U')
	{
		(arg->type == 'd' || arg->type == 'i') ? (digit = va_arg(ap, int))
							: (digit = va_arg(ap, unsigned int));
		st_int = (ft_checknegative(digit)) ? ft_itoa(-digit, check_base(arg))
				: ft_itoa(digit, check_base(arg));
		arg->neg = (ft_checknegative(digit)) ? 1 : 0;
	}
	else if (arg->length == 1 && arg->type != 'U')
	{
		(arg->type == 'd' || arg->type == 'i') ? (digit = (char)va_arg(ap, int))
							: (digit = (unsigned char)va_arg(ap, unsigned int));
		st_int = (ft_checknegative(digit)) ? ft_itoa(-digit, check_base(arg))
				: ft_itoa(digit, check_base(arg));
		arg->neg = (ft_checknegative(digit)) ? 1 : 0;
	}
	else
		st_int = print_d_i_ext(arg, ap, check_base(arg));
	if (arg->type == 'x')
		ft_tolower(st_int);
	return (st_int);
}

char		*print_p(t_param *arg, va_list ap)
{
	char				*store_pointer;
	void				*store_void;
	unsigned long long	nbr;

	if (arg->type == 'p')
	{
		store_void = va_arg(ap, void*);
		nbr = (unsigned long long)store_void;
		store_pointer = ft_itoa(nbr, 16);
		ft_tolower(store_pointer);
	}
	else
		return (NULL);
	return (store_pointer);
}
