#include <stdlib.h>
#include "getline.h"
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

void		first_read(t_getline *getline, char **symbol, int *read_count)
{
	if (ft_strlen(getline->buffer) == 0)
	{
		*read_count = read(getline->file_descriptor, getline->buffer,
						getline->buffer_size);
		getline->should_stop = 0;
		getline->buffer[getline->buffer_size] = '\0';
		*symbol = ft_strchr(getline->buffer, '\n');
	}
	else
	{
		*read_count = ft_strlen(getline->buffer);
		*symbol = ft_strchr(getline->buffer, '\n');
	}
}

void		continue_read(t_getline *gnl, char **symbol, char **line,
						int *r_cnt)
{
	while (*r_cnt != 0 || *symbol != NULL && **symbol != '\n')
	{
		gnl->prev_line_size = ft_strlen(*line);
		*line = ft_realloc(*line, gnl->prev_line_size, *r_cnt + 1);
		if ((*symbol = ft_strchr(gnl->buffer, '\n')) != NULL)
			*r_cnt = (int)(*symbol - gnl->buffer);
		ft_memcpy(&(*line)[gnl->prev_line_size], gnl->buffer, *r_cnt + 1);
		(*line)[gnl->prev_line_size + *r_cnt] = '\0';
		if (*symbol == NULL || **symbol != '\n')
		{
            *r_cnt = read(gnl->file_descriptor, gnl->buffer, gnl->buffer_size);
            gnl->buffer[*r_cnt] = '\0';
        }
		else
		{
			ft_memmove((void *)gnl->buffer, *symbol + 1,
					ft_strchr(*symbol, '\0') - *symbol);
			break ;
		}
		if (*r_cnt == 0)
		{
			gnl->should_stop = 1;
			break ;
		}
		gnl->buffer[gnl->buffer_size] = '\0';
		*symbol = ft_strchr(gnl->buffer, '\n');
	}
}

int			getline_next(t_getline *getline, char **line, int force_read)
{
	char			*symbol;
	int				read_count;

	if (!getline->should_stop && !force_read)
	{
		first_read(getline, &symbol, &read_count);
		if (read_count <= 0)
			return (read_count);
		if (symbol == NULL || *symbol == '\n')
		{
			*line = malloc(sizeof(char) * 1);
			*line[0] = '\0';
			continue_read(getline, &symbol, line, &read_count);
			return (1);
		}
	}
	return (0);
}

t_getline	start_getline(char *filename, unsigned buffer_size)
{
	t_getline	getline;

	getline.should_stop = 0;
	getline.buffer_size = buffer_size;
	getline.buffer = malloc(sizeof(char) * buffer_size + 1);
	getline.buffer[0] = '\0';
	getline.file_descriptor = open(filename, O_RDONLY);
	return (getline);
}

void		stop_getline(t_getline *get_line)
{
	free(get_line->buffer);
	close(get_line->file_descriptor);
}
