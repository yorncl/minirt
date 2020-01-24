
#ifndef BMPSAVE_H
# define BMPSAVE_H

#include <raytracerstruct.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//CHECK IF OK ON MAC
typedef struct	s_fileheader
{
	unsigned char	id[2];
	unsigned int	size;
	unsigned int	reserved;
	unsigned int	offset;
}				t_fileheader;

typedef struct	s_dibheader
{
	unsigned int		headersize;
	unsigned short int	width;
	unsigned short int	height;
	unsigned short int 	pane;
	unsigned short int	bytesperpixel;
}				t_dibheader;

void	init_fileheader(t_fileheader *fh, t_minirt *rt);
void	init_dibheader(t_dibheader *dib, t_minirt *rt);

int	write_bmp(t_minirt *rt, char *filename);



typedef struct	s_frame_saver
{
	unsigned char	*buffer;
	size_t			index;
	size_t			size;
}				t_frame_saver;

int				save_first_frame(t_minirt *mlx, char *filename);


#endif