#include "ft_printf.h"

u64 print_f(const char *fmt, t_dlisthead *args)
{
	u32 i;
	const char *s;
	const char *e;
	u64 total;
	
	total = 0;
	i = 0;
	s = fmt;
	while (*s)
	{
		e = s;
		while (*e && *e != '%')
			++e;
		total += write(1, s, e - s);
		s = e;
		if (*s == '%')
			total += print_spec(&s, args, (++i, &i));
		s += !!*s;
	}
	return (total);
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	t_dlisthead *args;
	u64 total;

	va_start(ap, fmt);
	args = parse_fmt(fmt, ap);
	total = print_f(fmt, args);
	//ftext_lstiter(args, &dump_state);
	va_end(ap);
	ftext_lstdel(&args, free_format);
	return (total);
}
