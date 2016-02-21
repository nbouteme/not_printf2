#include "ft_printf.h"

/*
** Trie la liste en fonction de l'ordre d'utilisation des parametres
** Permet d'éviter de trop compter sur la seconde passe.
 */
int cmp_forder(const t_dlist *_a, const t_dlist *_b)
{
	t_fmt *a;
	t_fmt *b;

	a = _a->content;
	b = _b->content;
	return (a->param - b->param);
}

/*
** Copie les données référencé du tableau datas de la fonction
** fill_data.(Callback)
*/
void save_data(t_dlist *e, t_data_param *arg)
{
	t_fmt *f;

	f = e->content;
	f->data = ft_memcpy(malloc(sizeof(t_data)), f->data, sizeof(t_data));
}

/*
** Callback utilisé pour déterminer le nombre d'arguments passés
 */
void max_n(t_dlist *e, int *max)
{
	t_fmt *f;

	f = e->content;
	if (f->param > *max)
		*max = f->param;
	if (f->width_i > *max)
		*max = f->param;
	if (f->precision_i > *max)
		*max = f->param;
}

/*
** read_and_fill se content de déterminer si un parametre doit etre lu
** ou non, et peut causer quelques assignations redondant but whatever.
 */
void read_and_fill(t_dlist *e, t_data_param *arg)
{
	t_fmt *f;

	f = e->content;
	if (f->width_i > 0)
		f->width = (long)pop_take_or_gtfo(f->width_i, arg);
	if (f->width_i == 0 && f->width == -1)
		f->width = (long)pop_take_or_gtfo(f->param - 1 - f->precision < 0, arg);
	if (f->precision_i > 0)
		f->precision = (long)pop_take_or_gtfo(f->precision_i, arg);
	if (f->param == arg->i)
	{
		f->data = &arg->datas[arg->i];
		f->data->c = pop_take_or_gtfo(f->param, arg);
	}
}
