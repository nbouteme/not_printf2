/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:06:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 14:16:33 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_u64			f_print_per(t_fmt *arg)
{
	t_u64 tot;

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

t_u64			f_print_u(t_fmt *a)
{
	t_u64	tot;
	t_u64	disp;
	t_i8	*top;
	t_s64	n;

	tot = 0;
	disp = (t_u64)a->data->c;
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

t_u64			f_print_c(t_fmt *arg)
{
	t_u64 tot;

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

t_u64			f_print_bs(t_fmt *arg)
{
	(void)arg;
	return (0);
}

t_u64			print_spec(const char **s, t_dlisthead *args, t_u32 *i)
{
	t_fmt f;
	t_fmt *to_print;

	f = i_parse_spec(s, i);
	to_print = ftext_lstfind(args, (void*)&cmp_spec, &f)->content;
	if (ft_tolower(to_print->type.c) != 's')
		truncate_val(to_print);
	return (fun_at(to_print->type.c)(to_print));
}
