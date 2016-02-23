/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:05:51 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/23 16:12:22 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

u64 f_print_o(t_fmt *a)
{
	u64 tot;
	u64 disp;
	char *top;
	s64 n;

	tot = 0;
	disp = (u64)a->data->c;
	top = ft_luitoa(disp, "01234567");
	n = ft_strlen(top);
	a->flags[0] |= a->width < 0;
	disp = a->width - n - (a->precision >= 0 ? a->precision : 0);
	if(a->width > n && !a->flags[0])
		tot += print_n(disp - a->flags[4], " 0"[a->flags[3]]);
	if(a->flags[4] && (top[0] - 48))
		(tot += write(1, "0", 1)) && a->width--;
	if(a->precision >= 0 && !a->flags[3])
		tot += print_n(a->precision - (a->flags[4] && (top[0] - 48)) - n, '0');
	tot += write(1, top, n);
	if (a->flags[0])
		tot += print_n(a->width - (a->precision >= 0) - n, ' ');
	free(top);
	return (tot);
}
