/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:18:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 14:12:17 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

t_u64			f_print_p(t_fmt *arg)
{
	arg->flags[4] = 1;
	return (f_print_x(arg));
}

t_u64			f_print_naught(t_fmt *a)
{
	(void)a;
	return (~0l);
}

t_fmt_fun		fun_at(char c)
{
	int i;

	i = 0;
	while (i < 10)
		if (g_kek[i].c == c)
			return (g_kek[i].f);
		else
			++i;
	return (&f_print_naught);
}

void			truncate_val(t_fmt *a)
{
	t_u64 val;

	if ((a->type.c != 'x' && a->type.c != 'o' && a->type.c != 'u')
		|| a->type.lf)
		return ;
	val = (t_u64)a->data->c;
	val &= ((1l << (a->length << 3)) - 1);
	a->data->c = (void *)val;
}

t_u64			print_n(t_i64 n, char c)
{
	void *m;

	if (n <= 0)
		return (0);
	m = malloc(n);
	ft_memset(m, c, n);
	write(1, m, n);
	free(m);
	return (n);
}
