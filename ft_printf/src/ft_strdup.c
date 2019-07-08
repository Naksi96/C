/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:40:34 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 20:03:18 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *src, int n)
{
	char *dup;

	if (!(dup = ft_strnew(n)))
		return (NULL);
	ft_strncpy(dup, src, n);
	return (dup);
}

char	*ft_strdup(const char *src)
{
	char	*dup;

	if (!(dup = ft_strnew(ft_strlen(src))))
		return (0);
	ft_strcpy(dup, src);
	return (dup);
}

size_t	w_strlen(unsigned *str)
{
	size_t len;

	len = 0;
	while (*str != L'\0')
	{
		len++;
		++str;
	}
	return (len);
}

char	*ft_wstrdup(wchar_t *wchar)
{
	int		i;
	char	*tmp_str;
	int		len;

	i = 0;
	len = (int)w_strlen((unsigned *)wchar);
	tmp_str = ft_strnew(len);
	while (*((unsigned *)wchar) != L'\0')
	{
		tmp_str[i] = *wchar;
		wchar++;
		i++;
	}
	return (tmp_str);
}
