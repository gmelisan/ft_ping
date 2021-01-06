/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:03:23 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/06 21:53:21 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "ft_ping.h"

/*
** ipv6 - if true, out is (struct sockaddr_in6 *)
** else out is (struct sockaddr_in *)
*/

void		resolve4(const char *dst, struct sockaddr_in *out)
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *ai;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_RAW;
	if (getaddrinfo(dst, NULL, &hints, &result) != 0)
		fatal("getaddrinfo: error while resolving address '%s'", dst);
	ai = result;
	while (ai)
	{
		if (ai->ai_family == AF_INET)
		{
			ft_memcpy(out, ai->ai_addr, sizeof(struct sockaddr_in));
			break ;
		}
		ai = ai->ai_next;
	}
	freeaddrinfo(result);
}

void		resolve6(const char *dst, struct sockaddr_in6 *out)
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *ai;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_RAW;
	if (getaddrinfo(dst, NULL, &hints, &result) != 0)
		fatal("getaddrinfo: error while resolving address '%s'", dst);
	ai = result;
	while (ai)
	{
		if (ai->ai_family == AF_INET6)
		{
			ft_memcpy(out, ai->ai_addr, sizeof(struct sockaddr_in6));
			break ;
		}
		ai = ai->ai_next;
	}
	freeaddrinfo(result);
}
