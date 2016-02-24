/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 13:25:28 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/24 13:54:38 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft/std.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "cdecl"

typedef struct	s_type
{
	t_s32		lf;
	t_s8		c;
}				t_type;

typedef struct	s_data
{
	t_s32		i;
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
	t_s32		param;
	t_s32		flags[5];
	t_s64		width_i;
	t_s64		precision_i;
	t_type		type;
	t_s32		length;
	t_s32		width;
	t_s32		precision;
	t_data		*data;
}				t_fmt;

typedef t_u64	(*t_fmt_fun)	(t_fmt *);

typedef struct	s_va
{
	t_u32		offset;
	t_u32		unknown1;
	void		*unknown2;
	void		*region;
}				t_va;

typedef struct	s_fmt_fun_assoc
{
	char		c;
	t_fmt_fun	f;
}				t_fmt_fun_assoc;

t_fmt_fun		fun_at(char c);
void			truncate_val(t_fmt *a);
t_dlist			*parse_spec(const char **s, t_u32 *n);
t_dlisthead		*parse_fmt(const char *s, va_list ap);
t_fmt			i_parse_spec(const char **s, t_u32 *n);
void			free_format(void *content, size_t size);
void			parse_type(const char **s, t_fmt *f);
void			parse_length(const char **s, t_fmt *f);
void			read_and_fill(t_dlist *e, t_data_param *arg);
void			max_n(t_dlist *e, t_i32 *max);
void			save_data(t_dlist *e, t_data_param *arg);
void			fill_data(t_dlisthead *l, va_list ap);
void			*pop_take_or_gtfo(t_i64 i, t_data_param *arg);
void			parse_width(const char **s, t_fmt *f, t_u32 *i);
void			parse_precision(const char **s, t_fmt *f, t_u32 *i);
void			parse_flags(const char **s, t_fmt *f);
void			infer_flags(t_fmt *f);
void			parse_parameter(const char **s, t_fmt *f);
int				ft_vprintf(const char *fmt, va_list ap);

t_u64				f_print_p(t_fmt *arg);
t_u64				f_print_naught(t_fmt *a);
t_u64				print_n(t_i64 n, char c);
t_u64				f_print_per(t_fmt *arg);
t_u64				f_print_u(t_fmt *a);
t_u64				f_print_c(t_fmt *arg);
t_u64				f_print_bs(t_fmt *arg);
t_u64				print_spec(const char **s, t_dlisthead *args, t_u32 *i);
t_u64				print_spec(const char **s, t_dlisthead *args, t_u32 *i);
t_i32				cmp_forder(const t_dlist *ba, const t_dlist *bb);
t_i32				cmp_spec(t_dlist *e, t_fmt *f);
t_u64				f_print_s(t_fmt *arg);
t_u64				f_print_d(t_fmt *a);
t_u64				print_n(t_i64 n, char c);
t_u64				f_print_o(t_fmt *a);
t_u64				f_print_x(t_fmt *a);

#endif
