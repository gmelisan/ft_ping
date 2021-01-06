/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:40:19 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/06 21:45:19 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_ping.h"

int		info(const char *fmt, ...)
{
	va_list ap;

	if (g_options.q)
		return (0);
	va_start(ap, fmt);
	ft_vfdprintf(2, fmt, ap);
	ft_fdprintf(2, "\n");
	va_end(ap);
	return (0);
}

int		error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	ft_fdprintf(2, "error: ");
	ft_vfdprintf(2, fmt, ap);
	ft_fdprintf(2, "\n");
	va_end(ap);
	return (-1);
}

void	fatal(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	ft_fdprintf(2, "fatal: ");
	ft_vfdprintf(2, fmt, ap);
	ft_fdprintf(2, "\n");
	va_end(ap);
	exit(1);
}

char	*generate_icmp_data()
{
	static char buf[ICMP_DATA_SIZE];
	size_t i;

	if (*buf)
		return (buf);
	i = 0;
	while (i < sizeof(buf) - 1)
	{
		buf[i] = i + '0';
		++i;
	}
	buf[i] = 0;
	return (buf);
}
