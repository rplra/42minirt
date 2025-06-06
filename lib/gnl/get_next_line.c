/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:32:14 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 17:58:09 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// Reads from fd > stores into buffer > updates surplus until /n found
char	*gnl_read(int fd, char *surplus)
{
	char		*buffer;
	ssize_t		rbytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rbytes = 1;
	while (rbytes > 0)
	{
		rbytes = read(fd, buffer, BUFFER_SIZE);
		if (rbytes == -1)
		{
			free(buffer);
			free(surplus);
			return (NULL);
		}
		buffer[rbytes] = '\0';
		surplus = ft_strjoin_free(surplus, buffer);
		if (ft_strchr(surplus, '\n'))
			break ;
	}
	return (free(buffer), surplus);
}

// Extract lines read up to newline
char	*gnl_extract(char *surplus)
{
	char	*line;
	size_t	len;

	if (!surplus || surplus[0] == '\0')
		return (NULL);
	len = 0;
	while (surplus[len] != '\n' && surplus[len] != '\0')
		++len;
	if (surplus[len] == '\n')
		++len;
	line = ft_substr(surplus, 0, len);
	return (line);
}

// Processes read lines, trim read lines up to /n, return line after /n
char	*gnl_process(char *surplus)
{
	char	*newline;
	size_t	i;

	if (!surplus || surplus[0] == '\0')
		return (free(surplus), NULL);
	i = 0;
	while (surplus[i] != '\n' && surplus[i] != '\0')
		++i;
	if (surplus[i] == '\0')
		return (free(surplus), NULL);
	if (surplus[i] == '\n')
		++i;
	newline = ft_substr(surplus, i, ft_strlen(surplus));
	return (free(surplus), newline);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = gnl_read(fd, buffer);
	line = gnl_extract(buffer);
	buffer = gnl_process(buffer);
	return (line);
}

/*
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	printf("fd     : %d\n", fd);
	printf("buffer : %d\n", BUFFER_SIZE);
	
	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	char *line3 = get_next_line(fd);
	char *line4 = get_next_line(fd);
	printf("read   : %s", line1);
	printf("read   : %s", line2);
	printf("read   : %s", line3);
	printf("read   : %s", line4);

	free(line1);
	free(line2);
	free(line3);
	free(line4);
	close(fd);
	return (0);
}
*/

/*
	STATIC VARIABLE
	- live for the program's execution
	- automatically zero-initialized
	- stored in data segment
	vs
	LOCAL VARS
	- confined to their block
	- live only during block execution
	- need explicit initialization, else contains garbage value
	- stored on stack

	<fcntl.h>
	OPEN()
	int open (const char *path, int flags [,int mode]);
	- path	; filename of fiel to open / create
	- flags	; O_RDONLY read-only, etc
	- int	; return value

	READ()
	ssize_t read(int fd, void *buf, size_t nbyte)
	- fd	; target file
	- buf	; to read into
	- nbytes; size of data to read
*/