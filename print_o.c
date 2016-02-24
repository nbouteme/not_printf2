/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:05:51 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 11:21:41 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include "ft_printf.h"

static i64	max(i64 a, i64 b)
{
	return (a > b ? a : b);
}

static int	calc_size(t_fmt *a, i64 len)
{
	int	total;

	total = max(len, a->precision) + (!a->flags[0] &&
		(a->flags[1] || a->flags[2]));
	total += a->flags[4];
	return (total);
}

static u64	actually_write_this_shit(t_fmt *a, i64 len, char *t)
{
	u64 total;

	total = 0;
	if (a->flags[4] && t[0] - 48)
	{
		total += print_n(1, '0');
		a->precision -= !a->width;
		a->width -= !a->flags[0];
	}
	total += print_n(a->precision - len, '0');
	if (a->flags[4] || t[0] - 48)
		total += write(1, t, len);
	else if (a->width > 0)
		total += write(1, " ", 1);
	return (total);
}

u64			f_print_o(t_fmt *a)
{
	u64	r;
	i64	d;
	i8	*t;
	i64	n;
	i64 w;

	r = 0;
	d = (u64)a->data->c;
	t = ft_luitoa(d, "01234567");
	n = ft_strlen(t);
	a->flags[3] &= a->precision < 0;
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->precision = a->flags[3] ? a->width - (a->width > n) : a->precision;
	a->width = a->flags[3] ? 0 : a->width;
	w = calc_size(a, n);
	if (!a->flags[0])
		r += print_n(a->width - w, ' ');
	r += actually_write_this_shit(a, n, t);
	if (a->flags[0])
		r += print_n(a->width - w, ' ');
	free(t);
	return (r);
}
