#include "ft_printf.h"

void parse_parameter(const char **s, t_fmt *f)
{
	const i8 *str;

	if (**s != '%')
		return ;
	0[s]++;
	str = *s;
	while (ft_strindexof("0123456789", *str) != -1)
		str++;
	if (*str == '$')
	{
		f->param = ft_atoi(*s);
		*s = str + 1;
	}
}

void infer_flags(t_fmt *f)
{
	if (f->precision_i > 0 || f->precision >= 0)
		f->flags[3] = 0;
	if (f->flags[0])
		f->flags[3] = 0;
	if (f->flags[1])
		f->flags[2] = 0;
}

void parse_flags(const char **s, t_fmt *f)
{
	s32 i;

	while ((i = ft_strindexof("-+ 0#", **s)) != -1)
	{
		f->flags[i] = 1;
		0[s]++;
	}
}

void parse_precision(const char **s, t_fmt *f, u32 *i)
{
	f->precision_i = -1;
	f->precision = -1;
	if (**s != '.')
		return ;
	s[0]++;
	if (s[0][0] == '*')
	{
		s[0]++;
		i[0]++;
		f->precision_i = ft_isdigit(s[0][0]) ? ft_atoi(s[0])
			: i[0] - 1;
		while (ft_isdigit(s[0][0])) s[0]++;
		s[0] += s[0][0] == '$';
		return ;
	}
	f->precision = ft_atoi(*s);
	while (ft_isdigit(0[0[s]]))
		0[s]++;
}

void parse_width(const char **s, t_fmt *f, u32 *i)
{
	if (s[0][0] == '*' && ++i[0] && ++s[0])
	{
		f->width_i = ft_isdigit(s[0][0]) ? ft_atoi(s[0])
			: i[0] - 1;
		while (ft_isdigit(s[0][0])) s[0]++;
		s[0] += s[0][0] == '$';
		return ;
	}
	if (!(**s == '-' || ft_isdigit(**s)))
		return ;
	f->width = ft_atoi(*s);
	while (ft_isdigit(0[0[s]]))
		0[s]++;
}
