/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:32:25 by ahuber            #+#    #+#             */
/*   Updated: 2021/10/24 11:14:19 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#include <stdio.h> // Pour printf dans main()
//#include <fcntl.h> // pareil
void	ft_read(int fd, char *buffer, char **fd_ligne)
{
	int		read_nbr;
	char	*tmp;

	read_nbr = read(fd, buffer, BUFFER_SIZE);
	while (read_nbr > 0)
	{
		buffer[read_nbr] = 0;
		if (!*fd_ligne)
			*fd_ligne = ft_substr(buffer, 0, read_nbr);
		else
		{
			tmp = *fd_ligne;
			*fd_ligne = ft_strjoin(*fd_ligne, buffer);
			free(tmp);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		read_nbr = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
}

char	*principale(char **fd_ligne)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	if (!*fd_ligne)
		return (NULL);
	if (!ft_strchr(*fd_ligne, '\n'))
	{
		ret = ft_substr(*fd_ligne, 0, ft_strlen(*fd_ligne));
		free(*fd_ligne);
		*fd_ligne = 0;
		if (ret[0] != '\0')
			return (ret);
		else
			free(ret);
		return (NULL);
	}
	i = ft_strlen(*fd_ligne);
	j = ft_strlen(ft_strchr(*fd_ligne, '\n'));
	ret = ft_substr(*fd_ligne, 0, i - j + 1);
	tmp = *fd_ligne;
	*fd_ligne = ft_substr(ft_strchr(*fd_ligne, '\n'), 1, j);
	free(tmp);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*fd_ligne;

	buffer = malloc(BUFFER_SIZE + 1);
	if (BUFFER_SIZE < 1 || fd == -1 || !buffer)
	{
		free(buffer);
		return (NULL);
	}
	ft_read(fd, buffer, &fd_ligne);
	return (principale(&fd_ligne));
}

/*int	main(int argc, char **argv)
{
	int	fd = open(argv[1], O_RDONLY);
	char	*retour = get_next_line(fd);
	int	i = 1;
	(void)argc;

	while (retour != NULL)
	{
		printf("%3i Retour fonction =%s",i , retour);
		//write(1, "/", 1);
		i++;
		retour = get_next_line(fd);
	}
		printf("%3i Retour fonction =%s",i , retour);
}*/
