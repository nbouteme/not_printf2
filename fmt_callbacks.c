#include "ft_printf.h"

/*
** Supprime un spécifieur
 */
void free_format(void *content, size_t size)
{
	t_fmt *f;

	f = content;
	free(f->data);
	free(f);
}

/*
** Callback utilisé pour retrouver le spécifieur qu'il faut afficher
** les quelques premiers membres de la structure permettent d'identifier
** uniquement un spécifieur
 */
int cmp_spec(t_dlist *e, t_fmt *f)
{
	t_fmt *a;

	a = e->content;
	return (ft_memcmp(f, a, sizeof(u32) * 6 + sizeof(u64) * 2) == 0);
}
