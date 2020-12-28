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

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <net/if.h>
# include <netinet/ip_icmp.h>
# include <sys/socket.h>
# include <errno.h>
# include "libft.h"

# define DEFAULT_TTL			250
# define ICMP_PACKET_SIZE		64
# define ICMP_DATA_SIZE			(ICMP_PACKET_SIZE - ICMP_MINLEN)

# define uchar					unsigned char
# define ushort					unsigned short
# define uint					unsigned int

extern struct	s_options
{
	int			D;
	int			t;
	int			v;
}				g_options;

struct			s_icmp_packet
{
	struct icmphdr	header;
	uchar			data[ICMP_PACKET_SIZE - sizeof(struct icmphdr)];
};

int		die(const char *fmt, ...);
void	resolve4(const char *dst, struct sockaddr_in *out);
void	resolve6(const char *dst, struct sockaddr_in6 *out);

#endif
