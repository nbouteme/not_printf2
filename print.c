#include "ft_printf.h"

u64 print_n(u64 n, char c)
{
	void *m;

	m = malloc(n);
	ft_memset(m, c, n);
	write(1, m, n);
	free(m);
	return (n);
}

u64 f_print_s(t_fmt *arg)
{
	u64 tot;
	u64 n;

	tot = 0;
	arg->data->c = arg->data->c ? arg->data->c : "(null)";
	n = ft_strlen(arg->data->c);
	n = arg->precision < 0 || arg->precision > n ? n : arg->precision;
	arg->flags[0] |= arg->width < 0;
	arg->width = arg->width < 0 ? -arg->width : arg->width;
	arg->width = arg->width <= n ? n : arg->width;
	if (arg->width > n && !arg->flags[0])
		tot += print_n(arg->width - n, ' ');
	if (arg->precision > 0)
		tot += write(1, arg->data->c, n);
	else
		tot += write(1, arg->data->c, n);
	if (arg->flags[0])
		tot += print_n(arg->width - n, ' ');
	return (tot);
}

u64 f_print_per(t_fmt *arg)
{
	u64 tot;

	tot = 0;
	arg->flags[0] |= arg->width < 0;
	arg->width = arg->width < 0 ? -arg->width : arg->width;
	arg->width = arg->width <= 1 ? 1 : arg->width;
	if (arg->width > 1 && !arg->flags[0])
		tot += print_n(arg->width - 1, ' ');
	tot += write(1, "%", 1);
	if (arg->flags[0])
		tot += print_n(arg->width - 1, ' ');
	return (tot);
}

u64 f_print_p(t_fmt *arg)
{
	return 0;
}

u64 f_print_d(t_fmt *arg)
{
	u64 tot;
	u64 disp;
	char *top;

	tot = 0;
	disp = arg->data->c | (arg->data->c & (0x80000000 * 0xFFFFFFFF00000000));
	top = ft_lsitoa(disp);
	free(top);

	arg->data->c = arg->data->c ? arg->data->c : "(null)";
	n = ft_strlen(top);
	arg->flags[0] |= arg->width < 0;
	arg->width = arg->width < 0 ? -arg->width : arg->width;
	if (arg->width > n && !arg->flags[0])
		tot += print_n(arg->width - n, ' ');
	if (arg->precision > 0)
		tot += write(1, arg->data->c, n);
	else
		tot += write(1, arg->data->c, n);
	if (arg->flags[0])
		tot += print_n(arg->width - n, ' ');
	return (tot);
}

u64 f_print_x(t_fmt *arg)
{
	return 0;
}

u64 f_print_o(t_fmt *arg)
{
	return 0;
}

u64 f_print_bx(t_fmt *arg)
{
	return 0;
}

u64 f_print_bo(t_fmt *arg)
{
	return 0;
}

u64 f_print_bs(t_fmt *arg)
{
	return 0;
}

typedef u64(*t_fmt_fun)(t_fmt *);

typedef struct	s_fmt_fun_assoc
{
	char c;
	t_fmt_fun f;
}				t_fmt_fun_assoc;

const t_fmt_fun_assoc g_kek[] =
{
	{ 's', &f_print_s },
	{ '%', &f_print_per },
	{ 'p', &f_print_p },
	{ 'd', &f_print_d },
	{ 'i', &f_print_d },
	{ 'x', &f_print_x },
	{ 'o', &f_print_o },
	{ 'X', &f_print_bx },
	{ 'O', &f_print_bo },
	{ 'S', &f_print_bs },
	{ 0, 0 }
};

t_fmt_fun fun_at(char c)
{
	int i;

	i = 0;
	while (i < 10)
		if (g_kek[i].c == c)
			return g_kek[i].f;
		else
			++i;
	return 0;
}

u64 print_spec(const char **s, t_dlisthead *args, u32 *i)
{
	t_fmt f;
	t_fmt *to_print;

	f = _parse_spec(s, i);
	to_print = ftext_lstfind(args, (void*) &cmp_spec, &f)->content;
	return fun_at(to_print->type.c)(to_print);
	return 1;
}
