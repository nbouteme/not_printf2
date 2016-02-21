#include "ft_printf.h"
#include <stdio.h>
#include <fcntl.h>

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

#define B_SIZE 64

char	*readfile(int fd)
{
	char	*buf;
	char	*tmp;
	char	*ret;
	int		n;

	ret = ft_strnew(1);
	buf = ft_strnew(B_SIZE + 1);
	while ((n = read(fd, buf, B_SIZE)) > 0)
	{
		tmp = ret;
		ft_bzero(buf + n, B_SIZE - n);
		ret = ft_strjoin(ret, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

char *get_out(int (*f)(const char *, va_list), const char *fmt, va_list ap)
{
	int out[2];
	int e;
	if ((e = pipe(out)) == -1)
	{
		perror("pipe");
		abort();
	}
	int so = dup(1);
	dup2(out[1], 1);
	close(out[1]);
	f(fmt, ap);
	fflush(stdout);
	fcntl(out[0], F_SETFL, O_NONBLOCK);
	char *ret = readfile(out[0]);
	dup2(so, 1);
	return ret;
}

void test_printf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void test_printf(const char *fmt, ...)
{
	va_list ap;
	va_list ad;

	va_start(ap, fmt);
	va_copy(ad, ap);

	char *v = get_out(vprintf, fmt, ap);
	char *ft_v = get_out(ft_vprintf, fmt, ad);
	if(strcmp(ft_v, v) == 0)
		printf("[OK]: %s\n", v), fflush(stdout);
	else
		printf("[FAIL]: Expected [%s], got [%s]\n", v, ft_v), fflush(stdout);
	va_end(ap);
}

int main(int argc, char *argv[])
{
	test_printf("%s", "train, train");
	test_printf("%5s", "train, train");
	test_printf("%*s", -5, "tr");
	test_printf("%5s", "tr");
	test_printf("%5.2s", "train, train");
	test_printf("%-5s", "train, train");
}
