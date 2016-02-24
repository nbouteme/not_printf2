/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:34:39 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 14:13:30 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_u64	f_print_s(t_fmt *arg)
{
	t_u64 tot;
	t_s64 n;

	tot = 0;
	arg->data->c = arg->data->c ? arg->data->c : "(null)";
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
