#include "ft_printf.h"

void parse_length(const char **s, t_fmt *f)
{
	s32 sz;
	s32 i;
	const i8 *one = "hljz";

	i = ft_strindexof(one, **s);
	sz = 4;
	f->type.lf = i == 1;
	if (i == 1)
		sz >>= 1;
	else if (i > 1)
		sz <<= 1;
	if (i != -1)
	{
		0[s]++;
		i = ft_strindexof(one, **s);
		if (i == 1)
			sz >>= 1;
		else if (i > 1)
			sz <<= 1;
	}
	f->length = sz;
}

void parse_type(const char **s, t_fmt *f)
{
	s32 i;
	const i8 *t = "diouxspXDOUSC%";

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

t_fmt _parse_spec(const char **s, u32 *n)
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
t_dlist *parse_spec(const char **s, u32 *n)
{
	t_fmt f;

	f = _parse_spec(s, n);
	return (ftext_lstnewelem(&f, sizeof(f)));
}

/*
** Construit une liste de format, les lies à leur données
*/

t_dlisthead *parse_fmt(const char *s, va_list ap)
{
	t_dlisthead *l;
	u32 i;

	l = ftext_lstnew();
	i = 0;
	while (*s)
	{
		if (*s == '%')
			ftext_lstpush_back(l, parse_spec(&s, (++i, &i)));
		++s;
	}
	//ftext_lstiter(l, &dump_state);
	fill_data(l, ap);
	return (l);
}
