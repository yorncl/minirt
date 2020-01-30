/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commonstruct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:25:10 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/30 13:00:02 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONSTRUCT_H
# define COMMONSTRUCT_H

# include <mlx.h>
# include <world.h>
# include <macro.h>

typedef struct	s_image
{
	void			*img;
	unsigned int	*imgdata;
	int				depth;
	int				linesize;
	int				edian;
}				t_image;
typedef struct	s_threadargs
{
	t_camera		*c;
	unsigned int	*img;
	t_world			*w;
	void			*rt;
	int				threadstart;
	int				threadend;
	int				id;
}				t_threadargs;

typedef struct	s_blockargs
{
	int		j;
	int		i;
	double	dx;
	double	dy;
}				t_blockargs;
#endif
