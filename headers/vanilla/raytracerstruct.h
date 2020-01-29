/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracerstruct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:37:04 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 15:27:36 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACERSTRUCT_H
# define RAYTRACERSTRUCT_H

# include <mlx.h>
# include <world.h>
# include <macro.h>
# include <commonstruct.h>

typedef struct	s_minirt
{
	void			*mlx;
	void			*win;
	t_image			*img;
	int				resx;
	int				resy;
	unsigned int	sizex;
	unsigned int	sizey;
	int				keys;
	int				realtime;
	t_world			*world;
}				t_minirt;
#endif
