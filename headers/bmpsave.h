/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpsave.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:03:22 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/25 15:55:19 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BMPSAVE_H
# define BMPSAVE_H

# include <raytracerstruct.h>
# include <macro.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_fileheader
{
	unsigned short int	id;
	unsigned int		size;
	unsigned int		reserved;
	unsigned int		offset;
}				t_fileheader;

typedef struct	s_dibheader
{
	unsigned int		headersize;
	unsigned int		width;
	unsigned int		height;
	unsigned short int	pane;
	unsigned short int	bitcount;
	unsigned char		offset[24];
}				t_dibheader;

int				write_fileheader(int fd, t_minirt *rt);
int				write_dibheader(int fd, t_minirt *rt);
int				write_pixeldata(int fd, t_minirt *rt);
int				write_bmp(t_minirt *rt, char *filename);

typedef struct	s_frame_saver
{
	unsigned char	*buffer;
	size_t			index;
	size_t			size;
}				t_frame_saver;

int				save_first_frame(t_minirt *mlx, char *filename);
#endif
