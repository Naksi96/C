/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 01:14:09 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 14:10:39 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int					ft_checknegative(long long n)
{
	if (n < 0)
		return (1);
	return (0);
}

char				*ft_itoa(unsigned long long n, unsigned int base)
{
	int					dilen;
	unsigned long long	tmp;
	char				*alpha;

	tmp = n;
	dilen = ft_countdigit(tmp, base);
	ERR_CHECK((alpha = ft_strnew(dilen + 1)));
	alpha[dilen + 1] = '\0';
	while (dilen > 0)
	{
		if (tmp % base < 10)
			alpha[dilen - 1] = (tmp % base) + '0';
		else
			alpha[dilen - 1] = (tmp % base) - 10 + 'A';
		dilen--;
		tmp /= base;
	}
	return (alpha);
}

unsigned long long	ft_power(int nbr, int n)
{
	unsigned long long	result;
	int					count;

	result = 1;
	count = n;
	while (count-- > 0)
		result *= nbr;
	return (result);
}

char				*fill_zerochar(int decpos)
{
	char	*tmp;

	tmp = ft_strnew(decpos);
	ft_memset(tmp, '0', decpos);
	return (tmp);
}

char				*ft_dtoa(long double d, t_param *arg)
{
	long double fl_uns;
	char		*alph;
	char		*whole;
	char		*dec;
	int			decpos;

	fl_uns = ((ft_checknegative(d)) ? (-d) : (d));
	arg->neg = ((ft_checknegative(d)) ? 1 : 0);
	ERR_CHECK((alph = ft_itoa(fl_uns, 10)));
	fl_uns = fl_uns - (long long)fl_uns;
	decpos = ((arg->precision == -1) ? 6 : (arg->precision));
	fl_uns *= ft_power(10, decpos);
	if ((fl_uns - (long long)fl_uns) >= 0.5)
		fl_uns += 1.0;
	if (decpos)
	{
		dec = (d) ? ft_itoa((long long)fl_uns, 10) : fill_zerochar(decpos);
		ERR_CHECK((whole = ft_strjoin(alph, ".")));
		free(alph);
		ERR_CHECK((alph = ft_strjoin(whole, dec)));
		free(dec);
		free(whole);
	}
	return (alph);
}
