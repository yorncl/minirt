/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtypes2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:31:38 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/25 16:37:20 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

void	add_square_sub(t_square *p, t_vec3 pos, t_vec3 i, t_vec3 j)
{
	p->p1 = v3add(pos, v3add(j, v3scale(i, -1)));
	p->p2 = v3add(pos, v3add(j, i));
	p->p3 = v3add(pos, v3add(v3scale(j, -1), i));
	p->p4 = v3add(pos, v3add(v3scale(j, -1), v3scale(i, -1)));
}
