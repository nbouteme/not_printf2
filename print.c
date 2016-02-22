#include "ft_printf.h"

u64 print_n(i64 n, char c)
{
	void *m;

	if(n <= 0)
		return (0);
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

u64 f_print_d(t_fmt *a)
{
	u64 tot;
	u64 disp;
	char *top;
	u64 n;

	tot = 0;
	disp = (u64)a->data->c | (!!((u64)a->data->c & (1L << 31)) * (~0L << 32));
	top = ft_lsitoa(disp, "0123456789");
	n = ft_strlen(top);
	a->precision > 0 && !a->flags[3] && (tot += print_n(a->precision - n, '0'));
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->width -= (a->flags[1] || a->flags[2]) && disp > 0;
	(a->flags[1] || a->flags[2]) && disp > 0 &&	write(1, &"+ "[a->flags[2]], 1)
		&& ++tot;
	disp = a->width - n - (a->precision > 0 ? a->precision : 0);
	a->width > n && !a->flags[0] && (tot += print_n(disp, " 0"[a->flags[3]]));
	tot += write(1, top, n);
	if (a->flags[0])
		tot += print_n(a->width - (a->precision > 0) - n, ' ');
	free(top);
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
