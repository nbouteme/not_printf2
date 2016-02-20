#include "ft_printf.h"

u64 print_spec(const char **s, t_dlisthead *args, u32 i)
{
	t_fmt f;
	t_fmt *to_print;

	f = _parse_spec(s, i);
	to_print = ftext_lstfind(args, (void*) &cmp_spec, &f)->content;
	if (to_print->type.c == 's')
		ft_putstr(to_print->data->c);
	return 1;
}
