/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:11:16 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 14:14:57 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Permet de récuperer le ième argument seulement si il a été déja lu.
** Dans le cas ou un argument se refere par position (avec le $), on
** peut récuperer sa valeur a condition que l'argument ai été consommé par
** va_arg.
** Par exemple, si le premier spécifieur référence le 5eme argument, on ne
** peut que le sauter jusqua ce qu'on ai consommé les 4 arguments avant.
** D'ou la seconde passe.
** fixme: void* est tout le temps utilisé, donc dans le cas ou un nombre
** flottant est nécessaire, ca pete.
*/

void	*pop_take_or_gtfo(long i, t_data_param *arg)
{
	if (arg->i == i && !arg->datas[i].c)
		arg->datas[arg->i].c = va_arg(*(va_list*)arg->ap, void*);
	if (arg->i >= i)
		return (arg->datas[i].c);
	return ((void*)i);
}

/*
** Détermine le nombre d'arguments, puis lis les valeurs stocké dans la liste.
*/

void	fill_data(t_dlisthead *l, va_list ap)
{
	int				max;
	t_data			*datas;
	t_data_param	tdp;

	max = -1;
	ftext_lstiterup(l, (void*)&max_n, &max);
	datas = ft_memalloc(++max * sizeof(*datas));
	tdp = (t_data_param) { 0, datas - 1, ap};
	while (++tdp.i < max)
		ftext_lstiterup(l, (void*)&read_and_fill, &tdp);
	ftext_lstiterup(l, (void*)&read_and_fill, &tdp);
	ftext_lstiter(l, (void*)&save_data);
	free(datas);
}
