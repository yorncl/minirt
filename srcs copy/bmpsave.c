/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpsave.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:03:27 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/25 16:36:05 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmpsave.h>

int		write_fileheader(int fd, t_minirt *rt)
{
	t_fileheader	fh;

	ft_bzero(&fh, sizeof(t_fileheader));
	fh.id = 19778;
	fh.size = 54 + rt->sizex * rt->sizey * 3;
	fh.reserved = 0;
	fh.offset = 54;
	if (
		write(fd, &fh.id, 2) == ERROR ||
		write(fd, &fh.size, 4) == ERROR ||
		write(fd, &fh.reserved, 4) == ERROR ||
		write(fd, &fh.offset, 4) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int		write_dibheader(int fd, t_minirt *rt)
{
	t_dibheader		dib;

	ft_bzero(&dib, sizeof(t_dibheader));
	dib.headersize = sizeof(t_dibheader);
	dib.width = rt->sizex;
	dib.height = rt->sizey;
	dib.pane = 1;
	dib.bitcount = 24;
	if (
		write(fd, &dib.headersize, 4) == ERROR ||
		write(fd, &dib.width, 4) == ERROR ||
		write(fd, &dib.height, 4) == ERROR ||
		write(fd, &dib.pane, 2) == ERROR ||
		write(fd, &dib.bitcount, 2) == ERROR ||
		write(fd, &dib.offset, 24) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int		write_pixeldata(int fd, t_minirt *rt)
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	y;
	unsigned char	*tab;

	if (!(tab = malloc(3 * rt->sizex * rt->sizey)))
		return (ERROR);
	i = 0;
	y = rt->sizey;
	while (--y > 0)
	{
		x = 0;
		while (x < rt->sizex)
		{
			tab[i * 3] = rt->img->imgdata[x + y * rt->sizex] >> 0;
			tab[i * 3 + 1] = rt->img->imgdata[x + y * rt->sizex] >> 8;
			tab[i * 3 + 2] = rt->img->imgdata[x + y * rt->sizex] >> 16;
			i++;
			x++;
		}
	}
	if (write(fd, tab, 3 * rt->sizex * rt->sizey) == ERROR)
		return (ERROR);
	free(tab);
	return (SUCCESS);
}

int		write_bmp(t_minirt *rt, char *filename)
{
	int				fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (ERROR);
	if (write_fileheader(fd, rt) == ERROR)
		return (ERROR);
	if (write_dibheader(fd, rt) == ERROR)
		return (ERROR);
	if (write_pixeldata(fd, rt) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
