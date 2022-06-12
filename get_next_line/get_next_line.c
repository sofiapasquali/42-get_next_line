/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shahn <shahn@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 02:01:26 by shahn             #+#    #+#             */
/*   Updated: 2022/06/11 20:51:20 by shahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_end(char *text)
{
	char	*end;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!*text)
	{
		free(text);
		return (NULL);
	}
	while (text[count] && text[count] != '\n')
		count++;
	end = (char *)malloc((sizeof(char) * (ft_strlen(text) - count) + 1));
	if (!end)
		return (NULL);
	if (text[count] == '\n')
		count++;
	while (text[count])
		end[i++] = text[count++];
	end[i] = '\0';
	free(text);
	return (end);
}

char	*cut_end(char *text)
{
	int		linesize;
	char	*result;
	int		i;

	i = 0;
	linesize = 0;
	if (!*text)
		return (NULL);
	while (text[linesize] && text[linesize] != '\n')
		linesize++;
	result = (char *)malloc(sizeof(char) * (linesize + 2));
	if (!result)
		return (NULL);
	while (text[i] && text[i] != '\n')
	{
		result[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
	{
		result[i] = '\n';
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*static_str;
	char			*result;
	static char		buffer[BUFFER_SIZE + 1];
	int				bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && ft_strchr(static_str, '\n') == NULL)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(static_str);
			return (NULL);
		}
		buffer[bytes] = '\0';
		static_str = ft_strjoin(static_str, buffer);
	}
	result = cut_end(static_str);
	static_str = get_end(static_str);
	return (result);
}
