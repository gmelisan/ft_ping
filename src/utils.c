/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:40:19 by gmelisan          #+#    #+#             */
/*   Updated: 2020/12/15 20:01:19 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int		die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	ft_vfdprintf(2, fmt, ap);
	ft_fdprintf(2, "\n");
	va_end(ap);
	exit(1);
	return (0);
}
