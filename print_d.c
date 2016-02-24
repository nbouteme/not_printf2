/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:38:02 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 10:21:50 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static i64	max(i64 a, i64 b)
{
	return (a > b ? a : b);
}

static int	calc_size(t_fmt *a, i64 len, i64 d)
{
	int	total;
	u8	neg;

	neg = d < 0;
	total = max(len, a->precision) + (!a->flags[0] &&
		(neg || a->flags[1] || a->flags[2]));
	return (total);
}

static u64	actually_write_this_shit(t_fmt *a, i64 len, char *t, char n)
{
	u64 total;

	total = 0;
	if (n)
	{
		total += write(1, "-", 1);
		a->width--;
	}
	else if (a->flags[1] || a->flags[2])
	{
		total += print_n(1, "+ "[a->flags[2]]);
		a->precision -= !a->width;
		a->width--;
	}
	total += print_n(a->precision - len, '0');
	if (a->precision || t[0] - 48)
		total += write(1, t, len);
	else if (a->width - len > 0)
		total += write(1, " ", 1);
	return (total);
}

u64			f_print_d(t_fmt *a)
{
	u64	r;
	i64	d;
	i8	*t;
	i64	n;
	i8	z;

	r = 0;
	d = (u64)a->data->c | (!!((u64)a->data->c & (1L << 31)) * (~0L << 32));
	d = a->type.lf ? (u64)a->data->c : d;
	t = ft_luitoa(d < 0 ? -d : d, "0123456789");
	n = ft_strlen(t);
	z = d < 0;
	a->flags[3] &= a->precision < 0;
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->precision = a->flags[3] ? a->width - (z && a->width > n) : a->precision;
	a->width = a->flags[3] ? 0 : a->width;
	if (!a->flags[0])
		r += print_n(a->width - calc_size(a, n, d), ' ');
	r += actually_write_this_shit(a, n, t, z);
	if (a->flags[0])
		r += print_n(a->width - calc_size(a, n, d), ' ');
	free(t);
	return (r);
}
