/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:09:56 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/10 14:09:42 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

#include <stdio.h>

int		parse_world(t_minirt *rt, char *path)
{
	int		fd;
	int		r;
	int		n;
	char	*line;

	n = 1;
	fd = open(path, O_RDONLY);
	line = 0;
	if (fd == -1)
		return (ERROR);
	while (1)
	{
		r = get_next_line(fd, &line);
		if (r == -1 || parse_line(rt, line, n) == -1)
		{
			free(line);
			return (ERROR);
		}
		n++;
		if (r == 0)
			return (SUCCESS);
	}
	return (SUCCESS);
}

int		parse_line(t_minirt *rt, char *line, int n)
{
	int offset;
	int (*parser)(t_minirt *rt, char *str);

	if (ft_strlen(line) == 0)
		return (SUCCESS);
	if (line[0] == '#')
		return (SUCCESS);
	if (parse_identifier(line, &parser, &offset) == ERROR)
	{
		parsing_error("Identifier not known", n);
		return (ERROR);
	}
	if (parser(rt, line + offset) == ERROR)
	{
		parsing_error("Identifier correct but line is wrong", n);
		return (ERROR);
	}
	return (SUCCESS);
}

int		parse_identifier(char *line,
			int (**parser)(t_minirt *rt, char *str),
			int *offset)
{
	*parser = 0;
	*offset = 1;
	if (line[0] == 'R')
		*parser = &parse_resolution;
	else if (line[0] == 'A')
		*parser = &parse_ambient;
	else if (line[0] == 'l')
		*parser = &parse_light;
	else if (line[0] == 'c' && line[1] == ' ' && ++*offset)
		*parser = &parse_camera;
	else if (line[0] == 's' && line[1] == 'p' && ++*offset)
		*parser = &parse_sphere;
	else if (line[0] == 'p' && line[1] == 'l' && ++*offset)
		*parser = &parse_plane;
	else if (line[0] == 's' && line[1] == 'q' && ++*offset)
		*parser = &parse_square;
	// else if (line[0] == 'c' && line[1] == 'y' && ++*offset)
	// 	*parser = &parse_cylinder;
	// else if (line[0] == 'c' && line[1] == 'y' && ++*offset)
	// 	parser = &parse_cylinder;
	if (*parser == 0)
		return (ERROR);
	return (SUCCESS);
}

int		parse_resolution(t_minirt *rt, char *line)
{
	rt->resx = 0;
	rt->resy = 0;
	while (ft_isspace(*line))
		line++;
	while (*line && ft_isdigit(*line))
	{
		rt->resx = rt->resx * 10 + *line - '0';
		line++;
	}
	while (ft_isspace(*line))
		line++;
	while (*line && ft_isdigit(*line))
	{
		rt->resy = rt->resy * 10 + *line - '0';
		line++;
	}
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	if (rt->resx == 0 || rt->resy == 0)
		return (ERROR);
	return (SUCCESS);
}

int		parsing_error(char *msg, int n)
{
	char *str;

	str = ft_itoa(n);
	write(1, "\e[1;31m", 7);
	write(1, msg, ft_strlen(msg));
	if (str)
	{
		write(1, " at line: ", 10);
		write(1, str, ft_strlen(str));
	}
	write(1, "\n\e[0m", 5);
	return (ERROR);
}

int		parse_vec3(t_vec3 *v, char *line)
{
	int		rd;
	int		r;
	int		i;
	double	*p;

	rd = 0;
	i = 3;
	p = &v->x;
	while (i--)
	{
		if ((r = parse_double(p, line)) == ERROR)
			return (ERROR);
		rd += r;
		line += r;
		if (i != 0 && *line++ != ',')
			return (ERROR);
		if (i != 0)
			rd++;
		p++;
	}
	return (rd);
}

int		parse_color(t_color *c, char *line)
{
	t_vec3	v;
	int		r;

	if ((r = parse_vec3(&v, line)) == ERROR || !v3drange(v, 0, 255))
		return (ERROR);
	c->color.r = v.x;
	c->color.g = v.y;
	c->color.b = v.z;
	return (r);
}

// Check for double size
int		parse_double(double *v, char *line)
{
	double	a;
	double 	coef;
	int		read;
	double	sign;

	a = 0;
	read = 0;
	coef = 1;
	sign = 1;
	while ((ft_isspace (*line) || *line == '-' || *line == '+') && ++read)
		if (*line++ == '-')
			sign *= -1;
	if (!ft_isdigit(*line))
		return (ERROR);
	while (ft_isdigit(*line) && ++read)
		a = a * 10 + *(line++) - '0';
	if (*line++ == '.' && ++read)
		while (ft_isdigit(*line))
		{
			coef /= 10;
			a += (double)((*(line++) - '0') * coef);
			read++;
		}
	// if (*[line - 1] )
	*v = a * sign;
	return (read);
}