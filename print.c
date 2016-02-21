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

u64 print_spec(const char **s, t_dlisthead *args, u32 *i)
{
	t_fmt f;
	t_fmt *to_print;

	f = _parse_spec(s, i);
	to_print = ftext_lstfind(args, (void*) &cmp_spec, &f)->content;
	if (to_print->type.c == 's')
		return (f_print_s(to_print));
	return 1;
}
