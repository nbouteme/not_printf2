/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:21:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 14:11:07 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		parse_length(const char **s, t_fmt *f)
{
	t_s32		i;
	const t_i8	*one = "hljz";

	i = ft_strindexof(one, **s);
	f->length = 4;
	if (i == -1)
		return ;
	f->type.lf = i == 1;
	f->length <<= !!i;
	f->length >>= !i;
	0[s]++;
	if (i != -1)
	{
		i = ft_strindexof(one, **s);
		if (i == -1)
			return ;
		0[s]++;
		f->length <<= !!i;
		f->length >>= !i;
	}
}

void		parse_type(const char **s, t_fmt *f)
{
	t_s32		i;
	const t_i8	*t = "diouxspXDOUSC%";

	i = ft_strindexof(t, **s);
	if ((ft_isupper(**s) || i >= 5) && **s != 'C')
		f->length = 8;
	f->type.c = **s;
	0[s]++;
}

/*
** Parse un spécificateur, et renvoie une structure contenant les infos lues.
** Apres parsing, le pointeur s pointe sur le dernier caractere du format.
** s: pointeur sur le format
** i: ième format parsé
*/

t_fmt		i_parse_spec(const char **s, t_u32 *n)
{
	t_fmt f;

	ft_bzero(&f, sizeof(f));
	f.param = -1;
	parse_parameter(s, &f);
	parse_flags(s, &f);
	parse_width(s, &f, n);
	parse_precision(s, &f, n);
	parse_length(s, &f);
	parse_type(s, &f);
	infer_flags(&f);
	f.param = f.param == -1 ? *n : f.param;
	0[s]--;
	return (f);
}

/*
** Wrapper qui renvoie la structure sous forme de maillon.
*/

t_dlist		*parse_spec(const char **s, t_u32 *n)
{
	t_fmt f;

	f = i_parse_spec(s, n);
	return (ftext_lstnewelem(&f, sizeof(f)));
}

/*
** Construit une liste de format, les lies à leur données
*/

t_dlisthead	*parse_fmt(const char *s, va_list ap)
{
	t_dlisthead	*l;
	t_u32		i;

	l = ftext_lstnew();
	i = 0;
	while (*s)
	{
		if (*s == '%')
		{
			++i;
			ftext_lstpush_back(l, parse_spec(&s, &i));
		}
		++s;
	}
	fill_data(l, ap);
	return (l);
}
