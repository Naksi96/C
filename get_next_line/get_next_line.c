/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:38:11 by doyang            #+#    #+#             */
/*   Updated: 2019/01/15 19:36:09 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_valid_file(const int fd, t_list **filelist)
{
	t_list			*search;

	if (!filelist)
		return (NULL);
	search = *filelist;
	while (search)
	{
		if ((int)search->content_size == fd)
			return (search);
		search = search->next;
	}
	search = ft_lstnew("", fd);
	ft_lstadd(filelist, search);
	return (search);
}

int		get_nl_pos(char **line, char *content, char c)
{
	size_t	i;

	i = 0;
	while (content[i] && content[i] != c)
		i++;
	*line = ft_strndup(content, i);
	if (!*line)
		return (0);
	return (i);
}

int		advread(const int fd, char **content)
{
	char	*tmp;
	char	buf[BUFF_SIZE + 1];
	int		readval;

	while ((readval = read(fd, buf, BUFF_SIZE)))
	{
		buf[readval] = '\0';
		tmp = *content;
		*content = ft_strjoin(tmp, buf);
		ERR_CHECK(*content);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (readval);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*filelist;
	t_list			*currfile;
	size_t			readval;
	char			*conthold;

	if (fd < 0 || !line || read(fd, buf, 0) < 0 ||
		!(currfile = get_valid_file(fd, &filelist)))
		return (-1);
	conthold = currfile->content;
	readval = advread(fd, &conthold);
	currfile->content = (char *)conthold;
	if (!readval && !*conthold)
		return (0);
	readval = get_nl_pos(line, currfile->content, '\n');
	conthold = currfile->content;
	if (conthold[readval] != '\0')
	{
		currfile->content = ft_strdup(&(conthold[readval + 1]));
		free(conthold);
	}
	else
		conthold[0] = '\0';
	return (1);
}

/*
** use linked list to store left over buffer.
** fd < 0 || !line || read(fd, buf, 0) || failed to call current file
** use content_size as fd (although not recommended) to find the correct file.
** if file doesn't exist, make new list, tmp->next (lstnew, lstadd)
** if there is \n, copy upto that pos to buf,
** and save the rest in tmp(t_list)
** if none, store all to buf and read again.
*/
