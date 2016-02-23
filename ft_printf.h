#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft/std.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_type
{
	s32		 	lf;
	s8		 	c;
}				t_type;

typedef struct	s_data
{
	s32			i;
	void		*c;
}				t_data;

typedef struct	s_data_param
{
	int			i;
	t_data		*datas;
	void		*ap;
}				t_data_param;

typedef struct	s_fmt
{
	s32			param;
	s32			flags[5];
	s64			width_i;
	s64			precision_i;
	t_type		type;
	s32			length;
	s32			width;
	s32			precision;
	t_data		*data;
}				t_fmt;

typedef struct	s_va
{
	u32			offset;
	u32			unknown1;
	void		*unknown2;
	void		*region;
}				t_va;

t_dlist			*parse_spec(const char **s, u32 *n);
t_dlisthead		*parse_fmt(const char *s, va_list ap);
t_fmt			_parse_spec(const char **s, u32 *n);
void			free_format(void *content, size_t size);
void			parse_type(const char **s, t_fmt *f);
void			parse_length(const char **s, t_fmt *f);
void			read_and_fill(t_dlist *e, t_data_param *arg);
void			max_n(t_dlist *e, i32 *max);
void			save_data(t_dlist *e, t_data_param *arg);
void			fill_data(t_dlisthead *l, va_list ap);
void			*pop_take_or_gtfo(i64 i, t_data_param *arg);
void			parse_width(const char **s, t_fmt *f, u32 *i);
void			parse_precision(const char **s, t_fmt *f, u32 *i);
void			parse_flags(const char **s, t_fmt *f);
void			infer_flags(t_fmt *f);
void			parse_parameter(const char **s, t_fmt *f);
u64				print_spec(const char **s, t_dlisthead *args, u32 *i);
i32				cmp_forder(const t_dlist *_a, const t_dlist *_b);
i32				cmp_spec(t_dlist *e, t_fmt *f);
int				ft_vprintf(const char *fmt, va_list ap);

int ft_printf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
u64 f_print_s(t_fmt *arg);
u64 f_print_d(t_fmt *a);
u64 print_n(i64 n, char c);
u64 f_print_o(t_fmt *a);
u64 f_print_x(t_fmt *a);

#endif
