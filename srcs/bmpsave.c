#include <bmpsave.h>

#include <stdio.h>
void	init_fileheader(t_fileheader *fh, t_minirt *rt)
{
	fh->id[0] = 'B';
	fh->id[1] = 'M';
	fh->size = sizeof(t_fileheader) + sizeof(t_dibheader) +
		rt->sizex * rt->sizey *sizeof(unsigned int);
	printf("MINE %u\n", fh->size);
	fh->size = (fh->size >> 8) | (fh->size << 8);
	printf("MINE %x\n", fh->size);
	fh->reserved = 0;
	fh->offset = sizeof(t_fileheader) + sizeof(t_dibheader);
}

void	init_dibheader(t_dibheader *dib, t_minirt *rt)
{
	dib->headersize = sizeof(t_dibheader);
	dib->width = rt->sizex;
	dib->height = rt->sizey;
	dib->pane = 1;
	dib->bytesperpixel = sizeof(unsigned int) * 8;
}

int	write_bmp(t_minirt *rt, char *filename)
{
	int				fd;
	t_fileheader	fh;
	t_dibheader		dib;

	fh = (t_fileheader) {0};
	dib = (t_dibheader) {0};
	fd = open(filename, O_WRONLY | O_CREAT);
	// if (fd == -1)
	// {
	// 	//CHOKE
	// }

	init_fileheader(&fh, rt);
	init_dibheader(&dib, rt);
	write(fd, &fh, sizeof(t_fileheader));
	write(fd, &dib, sizeof(t_dibheader));
	// write(fd, rt->img->imgdata, rt->sizex * rt->sizey *sizeof(unsigned int));
	return (0);
}












static void	iwrite(t_frame_saver *sv, unsigned int val)
{
	sv->buffer[sv->index++] = val >> 0;
	sv->buffer[sv->index++] = val >> 8;
	sv->buffer[sv->index++] = val >> 16;
	sv->buffer[sv->index++] = val >> 24;
}

/*
** file header
**
** "BM" (2o)
** file size (4o)
** null (2o)
** null (2o)
** 54,0,0,0 (4o)
*/

static void	write_file_header(t_frame_saver *sv)
{
	sv->buffer[sv->index++] = 'B';
	sv->buffer[sv->index++] = 'M';
	iwrite(sv, sv->size);
	printf("PLZ %ld\n", sv->size);
	iwrite(sv, 0x00000000);
	sv->buffer[sv->index++] = 54;
	sv->buffer[sv->index++] = 0;
	sv->buffer[sv->index++] = 0;
	sv->buffer[sv->index++] = 0;
}

/*
** file info
**
** 40,0,0,0 (4o)
** width (4o)
** height (4o)
** 1,0 (2o)
** 24,0 (2o)
** null (24o)
*/

static void	write_file_info(t_minirt *mlx, t_frame_saver *sv)
{
	int i;

	sv->buffer[sv->index++] = 40;
	sv->buffer[sv->index++] = 0;
	sv->buffer[sv->index++] = 0;
	sv->buffer[sv->index++] = 0;
	iwrite(sv, mlx->sizex);
	iwrite(sv, mlx->sizey);
	sv->buffer[sv->index++] = 1;
	sv->buffer[sv->index++] = 0;
	sv->buffer[sv->index++] = 24;
	sv->buffer[sv->index++] = 0;
	i = 0;
	while (i < 24)
	{
		sv->buffer[sv->index++] = 0;
		i++;
	}
}

// static void	write_body(t_minirt *mlx, t_frame_saver *sv)
// {
// 	int x;
// 	int y;

// 	y = mlx->sizey;
// 	while (y >= 0)
// 	{
// 		x = 0;
// 		while (x < mlx->sizex)
// 		{
// 			sv->buffer[sv->index++] = mlx->img->imgdata[y * mlx->sizex + x] >> 0;
// 			sv->buffer[sv->index++] = mlx->img->imgdata[y * mlx->sizex + x] >> 8;
// 			sv->buffer[sv->index++] = mlx->img->imgdata[y * mlx->sizex + x] >> 16;
// 			x++;
// 		}
// 		x = 0;
// 		while (x < (4 - (mlx->sizex * 3) % 4) % 4)
// 		{
// 			sv->buffer[sv->index++] = 0;
// 			x++;
// 		}
// 		y--;
// 	}
// }

int			save_first_frame(t_minirt *mlx, char *filename)
{
	int				fd;
	t_frame_saver	sv;

	sv = (t_frame_saver) { 0 };
	sv.size = 54 + 3 * mlx->sizex * mlx->sizey +
		((4 - (mlx->sizex * 3) % 4) % 4) * mlx->sizey;
	printf("HIS %lu\n", sv.size);
	sv.buffer = malloc(sv.size);
	if ((fd = open(filename, O_WRONLY | O_CREAT)) < 0)
		return (-1);
	write_file_header(&sv);
	write_file_info(mlx, &sv);
	// write(fd, mlx->img->imgdata, mlx->sizex * mlx->sizey * 4);
	write(fd, sv.buffer, sv.size);
	close(fd);
	return (0);
}