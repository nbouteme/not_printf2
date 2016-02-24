/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:13:03 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 14:14:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *g_xconv[] = {"0123456789abcdef", "0123456789ABCDEF"};
char *g_hash[] = {"0x", "0X"};

static t_i64		max(t_i64 a, t_i64 b)
{
	return (a > b ? a : b);
}

static int			calc_size(t_fmt *a, t_i64 len, t_i64 val)
{
	int	total;

	total = max(len, a->precision) + (!a->flags[0] &&
		(a->flags[1] || a->flags[2]));
	total += (a->flags[4] && val) << 1;
	return (total);
}

static t_u64		actually_write_this_shit(t_fmt *a, t_i64 len, char *t)
{
	t_u64 total;

	total = 0;
	if ((a->flags[4] && t[0] - 48) || a->type.c == 'p')
	{
		total += write(1, g_hash[a->type.c == 'X'], 2);
		a->width -= !a->flags[0] << 1;
	}
	total += print_n(a->precision - len, '0');
	if ((a->flags[4] && t[0] - 48) || (a->precision || t[0] - 48))
		total += write(1, t, len);
	else if (a->width > 0)
		total += write(1, " ", 1);
	return (total);
}

t_u64				f_print_x(t_fmt *a)
{
	t_u64	r;
	t_i64	d;
	t_i8	*t;
	t_i64	n;
	t_i64	w;

	r = 0;
	d = (t_u64)a->data->c;
	t = ft_luitoa(d, g_xconv[a->type.c == 'X']);
	n = ft_strlen(t);
	a->flags[3] &= a->precision < 0;
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->precision = a->flags[3] ? a->width - ((a->width > n && d) << 1) :
		a->precision;
	a->width = a->flags[3] ? 0 : a->width;
	w = calc_size(a, n, d);
	if (!a->flags[0])
		r += print_n(a->width - w, ' ');
	r += actually_write_this_shit(a, n, t);
	if (a->flags[0])
		r += print_n(a->width - w, ' ');
	free(t);
	return (r);
}
