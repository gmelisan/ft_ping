/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:29:46 by gmelisan          #+#    #+#             */
/*   Updated: 2020/12/15 21:16:17 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

#include <sys/socket.h>
# include "libft.h"

# define DEFAULT_TTL			250

extern struct	s_options
{
	int			D;
	int			t;
	int			v;
}				g_options;

int		die(const char *fmt, ...);
void	resolve4(const char *dst, struct sockaddr_in *out);
void	resolve6(const char *dst, struct sockaddr_in6 *out);

#endif
