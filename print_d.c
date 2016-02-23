/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:38:02 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/23 20:16:57 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int max(int a, int b)
{
	return a > b ? a : b;
}

int calc_size(t_fmt *a, i64 len, i64 d)
{
	int total;
	char neg;

	neg = d < 0;
	total = max(len, a->precision) + (!neg || a->flags[1] || a->flags[2]);
	return total;
}

u64 actually_write_this_shit(t_fmt *a, i64 len, char *t, char n)
{
	u64 total;

	total = 0;
	if (n)
		total += write(1, "-", 1);
	else if (a->flags[1] || a->flags[2])
		total += print_n(1, "+ "[a->flags[2]]);
	if (a->precision || t[0] - 48)
		total += write(1, t, len);
	return total;
}

u64 f_print_d(t_fmt *a)
{
	u64 r;
	i64 d;
	char *t;
	i64 n;
	char neg;

	r = 0;
	d = (u64)a->data->c | (!!((u64)a->data->c & (1L << 31)) * (~0L << 32));
	d = a->type.lf ? (u64)a->data->c : d;
	t = ft_luitoa(d < 0 ? -d : d, "0123456789");
	n = ft_strlen(t);
	neg = d < 0;
	a->flags[3] &= a->precision < 0;
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->precision = a->flags[3] ? a->width : a->precision;
	a->width = a->flags[3] ? 0 : a->width;
	int towrite = calc_size(a, n, d);
	if (a->flags[0])
		r += print_n(a->width - towrite, ' ');
	r += actually_write_this_shit(a, n, t, neg);
	if (!a->flags[0])
		r += print_n(a->width - towrite, ' ');
	free(t);
	return (r);
}
