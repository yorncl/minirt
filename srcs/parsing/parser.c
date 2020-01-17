/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:09:56 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/17 14:39:48 by mclaudel         ###   ########.fr       */
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
	int		flags;

	n = 1;
	fd = open(path, O_RDONLY);
	line = 0;
	flags = 0;
	if (fd == -1)
		return (ERROR);
	while (1)
	{
		r = get_next_line(fd, &line);
		if (!line || r == -1 || parse_line(rt, line, n, &flags) == ERROR)
		{
			free(line);
			return (ERROR);
		}
		free(line);
		n++;
		if (r == 0)
			break ;
	}
	if (!(flags & FLAG_CAMERA))
		return (parsing_error("Missing a camera !", -1));
	if (!(flags & FLAG_RES))
		return (parsing_error("Missing resolution !", -1));
	return (SUCCESS);
}

int		parse_line(t_minirt *rt, char *line, int n, int *flags)
{
	int offset;
	int (*parser)(t_minirt *rt, char *str);

	if (ft_strlen(line) == 0 || line[0] == '#')
		return (SUCCESS);
	if (parse_identifier(line, &parser, &offset) == ERROR)
		return (parsing_error("Identifier not known", n));
	if (parser == &parse_resolution)
	{
		if (*flags & FLAG_RES)
			return (parsing_error("You can only put one resolution", n));
		else
			*flags |= FLAG_RES;
	}
	if (parser == &parse_ambient)
	{
		if (*flags & FLAG_AMBIENT)
			return (parsing_error(
				"You can only put one ambient lights you dummie", n));
		else
			*flags |= FLAG_AMBIENT;
	}
	if (parser == &parse_camera)
		*flags |= FLAG_CAMERA;
	if (parser(rt, line + offset) == ERROR)
		return (parsing_error("Identifier correct but line is wrong", n));
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
	else if (line[0] == 'c' && line[1] == 'y' && ++*offset)
		*parser = &parse_cylinder;
	else if (line[0] == 't' && line[1] == 'r' && ++*offset)
		*parser = &parse_triangle;
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
	if (str && n != -1)
	{
		write(1, " at line: ", 10);
		write(1, str, ft_strlen(str));
	}
	write(1, "\n\e[0m", 5);
	free(str);
	return (ERROR);
}
