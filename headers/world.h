/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:27:41 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 23:27:41 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include <vec3.h>
#include <camera.h>

typedef enum 	obj_type{
	SPHERE,
}				obj_type;

typedef struct	obj3d
{
	vec3			pos;
	obj_type		type;
	int				w;
	unsigned int	color;
	struct obj3d	*next;
}				obj3d;

typedef struct 	s_world
{
	camera	*c;
	obj3d	*obj;
}				t_world;
#endif
