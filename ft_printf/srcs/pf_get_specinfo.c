/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_get_specinfo.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:09:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:55:31 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	void	init_specs(t_spec **info, char **precision, char **width)
{
	*precision = 0;
	*width = 0;
	*info = (t_spec*)malloc(sizeof(t_spec) * 1);
	(*info)->flags = 0;
	(*info)->width = 0;
	(*info)->width_on = 0;
	(*info)->precis = 0;
	(*info)->prec_on = 0;
	(*info)->type = 0;
	(*info)->type_size = 0;
}

static	void	field_specs(char *f, t_spec *info, char **p, char **w)
{
	if (info->prec_on == 1 && ft_isdigit(*f) == 1)
		*p = ft_stradd(*p, ft_ctostr(*f));
	if (info->prec_on == 0 && ft_isdigit(*f) == 1 && info->width_on == 1)
		*w = ft_stradd(*w, ft_ctostr(*f));
}

static	void	parse_typesize(t_spec *info)
{
	char	*flags;
	int		i;

	i = 0;
	flags = info->flags;
	if (flags == 0)
		return ;
	while (flags[i] != '\0')
	{
		if (info->type_size != 0)
			break ;
		if (flags[i] == 'h' && flags[i + 1] == 'h')
			info->type_size = -2;
		else if ((flags[i] == 'l' && flags[i + 1] == 'l') ||
				flags[i] == 'j')
			info->type_size = 2;
		else if (flags[i] == 'h')
			info->type_size = -1;
		else if (flags[i] == 'l' || flags[i] == 'z')
			info->type_size = 1;
		i++;
	}
}

static	void	load_fields(t_spec *info, char *p, char *w, char **format)
{
	if (info->prec_on == 1 && p != 0)
	{
		info->precis = ft_atoi(p);
		free(p);
	}
	if (info->width_on == 1 && w != 0)
	{
		info->width = ft_atoi(w);
		free(w);
	}
	pf_flag_override(info);
	parse_typesize(info);
	info->type = **format;
	if (info->type == 'U')
		info->type_size = 1;
	else if (ft_cinstr(info->flags, 'L') == 1 && info->type == 'f')
		info->type_size = 2;
}

t_spec			*pf_get_specinfo(char **format, t_spec *info)
{
	char	*precision;
	char	*width;

	init_specs(&info, &precision, &width);
	while (**format != '\0')
	{
		if (ft_cinstr("#-+0 jzlLh.123456789%cspdiouUxXf", **format) == 0)
			break ;
		else if (**format == '.')
			info->prec_on = 1;
		else if (ft_cinstr("123456789", **format) == 1 && info->prec_on == 0)
			info->width_on = 1;
		field_specs(*format, info, &precision, &width);
		if (ft_cinstr("#-+ lLhjz", **format) == 1)
			info->flags = ft_stradd(info->flags, ft_ctostr(**format));
		else if (**format == '0' && info->width_on == 0 && info->prec_on == 0)
			info->flags = ft_stradd(info->flags, ft_ctostr(**format));
		else if (ft_cinstr("%cspdiouUxXf", **format) == 1)
		{
			load_fields(info, precision, width, format);
			return (info);
		}
		*format = *format + 1;
	}
	return (info);
}
