/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:06:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 10:51:19 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

u64 f_print_u(t_fmt *a)
{
	u64 tot;
	u64 disp;
	char *top;
	s64 n;

	tot = 0;
	disp = (u64)a->data->c;
	top = ft_luitoa(disp, "0123456789");
	n = ft_strlen(top);
	a->precision > 0 && !a->flags[3] && (tot += print_n(a->precision - n, '0'));
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->width -= (a->flags[1] || a->flags[2]) && disp > 0;
	a->flags[1] && disp > 0 && (tot += write(1, " ", 1));
	disp = a->width - n - (a->precision > 0 ? a->precision : 0);
	a->width > n && !a->flags[0] && (tot += print_n(disp, " 0"[a->flags[3]]));
	(a->precision || top[0] - 48) && (tot += write(1, top, n));
	if (a->flags[0])
		tot += print_n(a->width - (a->precision > 0) - n, ' ');
	free(top);
	return (tot);
}

u64 f_print_p(t_fmt *arg)
{
	arg->flags[4] = 1;
	return f_print_x(arg);
}

u64 f_print_c(t_fmt *arg)
{
	u64 tot;

	tot = 0;
	arg->flags[0] |= arg->width < 0;
	arg->width = arg->width < 0 ? -arg->width : arg->width;
	arg->width = arg->width <= 1 ? 1 : arg->width;
	if (arg->width > 1 && !arg->flags[0])
		tot += print_n(arg->width - 1, ' ');
	tot += write(1, &arg->data->c, 1);
	if (arg->flags[0])
		tot += print_n(arg->width - 1, ' ');
	return (tot);
}

u64 f_print_bx(t_fmt *arg)
{
	(void)arg;
	return 0;
}

u64 f_print_bo(t_fmt *arg)
{
	(void)arg;
	return 0;
}

u64 f_print_bs(t_fmt *arg)
{
	(void)arg;
	return 0;
}

typedef u64(*t_fmt_fun)(t_fmt *);

typedef struct	s_fmt_fun_assoc
{
	char c;
	t_fmt_fun f;
}				t_fmt_fun_assoc;

u64 f_print_naught(t_fmt *a)
{
	(void)a;
	return (0);
}

const t_fmt_fun_assoc g_kek[] =
{
	{ 's', &f_print_s },
	{ '%', &f_print_per },
	{ 'p', &f_print_p },
	{ 'd', &f_print_d },
	{ 'i', &f_print_d },
	{ 'c', &f_print_c },
	{ 'u', &f_print_u },
	{ 'x', &f_print_x },
	{ 'o', &f_print_o },
	{ 'X', &f_print_x },
	{ 'U', &f_print_u },
	{ 'O', &f_print_o },
	{ 'S', &f_print_bs },
	{ 0, &f_print_naught }
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
	return &f_print_naught;
}

void truncate_val(t_fmt *a)
{
	u64 val;
	if ((a->type.c != 'x' && a->type.c != 'o' && a->type.c != 'u') || a->type.lf)
		return ;
	val = (u64)a->data->c;
	val &= ((1l << (a->length << 3)) - 1);
	a->data->c = (void *)val;
}

u64 print_spec(const char **s, t_dlisthead *args, u32 *i)
{
	t_fmt f;
	t_fmt *to_print;

	f = _parse_spec(s, i);
	to_print = ftext_lstfind(args, (void*) &cmp_spec, &f)->content;
	if (ft_tolower(to_print->type.c) != 's')
		truncate_val(to_print);
	return fun_at(to_print->type.c)(to_print);
}
