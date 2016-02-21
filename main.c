#include "ft_printf.h"
#include <stdio.h>

void dump_state(t_dlist *e)
{
	return;
	t_fmt *f = e->content;

	printf("[param: %d]"			"\n" 
		   "[flags: %c%c%c%c%c]"	"\n" 
		   "[width: %s]"			"\n" 
		   "[precision: %s]"		"\n" 
		   "[type: %c]\n",
		   f->param,
		   f->flags[0] ? '-' : 'x',
		   f->flags[1] ? '+' : 'x',
		   f->flags[2] ? ' ' : 'x',
		   f->flags[3] ? '0' : 'x',
		   f->flags[4] ? '#' : 'x',
		   f->width ? ft_itoa(f->width) : "unspecified",
		   f->precision != -1 ? ft_itoa(f->precision) : "unspecified",
		   f->type.c
		);
	printf("w index: %s\n\n", f->width_i > 0 ? ft_itoa(f->width_i) : "unspecified");
/*	printf("%s\n", f->data && f->type.c == 's' ? f->data->c : "");
	long disp = f->data && f->type.c == 'd' ? f->data->c : 0;
	if (disp & 0x8000000)
		disp |= 0xFFFFFFFF00000000;
		printf("%ld\n", disp);*/
}

int main(int argc, char *argv[])
{
	//ft_printf("%-5s\n", "tr");
	//ft_printf("%5s\n", "tr");
	ft_printf("%*s\n", -5, "tr");
	printf("%*s\n", -5, "tr");
	//printf("%5.2s\n", "train, train");
}
