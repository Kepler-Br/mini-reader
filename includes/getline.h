#ifndef MINI_READER_GETLINE_H
# define MINI_READER_GETLINE_H

typedef struct	s_getline
{
	int				file_descriptor;
	unsigned int	buffer_size;
	int				should_stop;
	char			*buffer;
	unsigned int	prev_line_size;
}				t_getline;

int				getline_next(t_getline *getline, char **line, int force_read);
t_getline		start_getline(char *filename, unsigned buffer_size);
void			stop_getline(t_getline *get_line);

#endif
