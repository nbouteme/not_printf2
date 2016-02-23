/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:38:02 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/23 17:51:23 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

u64 f_print_d(t_fmt *a)
{
	u64 tot;
	i64 disp;
	char *top;
	s64 n;
	char neg;

	tot = 0;
	disp = (u64)a->data->c | (!!((u64)a->data->c & (1L << 31)) * (~0L << 32));
	disp = a->type.lf ? (u64)a->data->c : disp;
	top = ft_luitoa(disp < 0 ? -disp : disp, "0123456789");
	n = ft_strlen(top);
	neg = disp < 0;
	a->flags[3] &= a->precision < 0;
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	if (!a->flags[3] && neg)
	{
		tot += print_n(n - (a->width +  (a->precision > 0 ? a->precision : 0)), ' ');
		write(1, "-", 1);
	}
	else if (a->flags[3] && neg)
	{
		write(1, "-", 1);
		print_n(n - (a->width +  (a->precision > 0 ? a->precision : 0)), '0');
	}
	else if (neg)
	{
		print_n(n - (a->width +  (a->precision > 0 ? a->precision : 0)), ' ');
		write(1, "-", 1);
	}
	else
	{
		print_n(n - (a->width +  (a->precision > 0 ? a->precision : 0)), ' ');
	}
	write(1, top, n);
	free(top);
	return (tot);
}
