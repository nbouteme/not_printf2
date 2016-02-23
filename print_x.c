/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:13:03 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/23 16:22:14 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *g_xconv[] = {"0123456789abcdef", "0123456789ABCDEF"};
char *g_hash[] = {"0x", "0X"};

u64 f_print_x(t_fmt *a)
{
	u64 tot;
	s64 disp;
	char *top;
	s64 n;

	tot = 0;
	disp = (u64)a->data->c;
	top = ft_luitoa(disp, g_xconv[a->type.c == 'X']);
	n = ft_strlen(top);
	a->flags[0] |= a->width < 0;
	a->width = a->width < 0 ? -a->width : a->width;
	a->width -= (a->flags[1] || a->flags[2]) && disp >= 0;
	a->width -= (a->flags[4] && (top[0] - 48 || a->type.c == 'p')) << 1;
	disp = a->width - n - (a->precision > n ? a->precision : 0);
	a->width > n && !a->flags[0] && (tot += print_n(disp, " 0"[a->flags[3]]));
	if(a->flags[4] && ((top[0] - 48) || a->type.c == 'p'))
		tot += write(1, g_hash[a->type.c == 'X'], 2);
	a->precision > 0 && !a->flags[3] && (tot += print_n(a->precision - n, '0'));
	(a->precision || top[0] - 48) && (tot += write(1, top, n));
	if (a->flags[0])
		tot += print_n(a->width - (a->precision > 0) - n, ' ');
	free(top);
	return (tot);
}
