/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:29:46 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/06 21:50:33 by gmelisan         ###   ########.fr       */
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
# define IP_HEADER_SIZE			20
# define RECV_TIMEOUT			1
# define DEFAULT_INTERVAL		1

# define uchar					unsigned char
# define ushort					unsigned short
# define uint					unsigned int

extern struct	s_options
{
	int			c; // count pings
	int			D; // print timestamp
	int			i; // interval between pings
	int			t; // TTL
	int			v; // verbose
	int			q; // quiet
	int			exit_flag;
}				g_options;

struct			s_icmp_packet
{
	struct icmphdr	header;
	//uchar			data[ICMP_PACKET_SIZE - sizeof(struct icmphdr)];
	uchar			data[ICMP_DATA_SIZE];
};

int		info(const char *fmt, ...);
int		error(const char *fmt, ...);
void	fatal(const char *fmt, ...);
void	resolve4(const char *dst, struct sockaddr_in *out);
void	resolve6(const char *dst, struct sockaddr_in6 *out);

struct s_icmp_packet	create_icmp(int seq, int id, char *data);
int						send_icmp(int sck, struct sockaddr_in sa,
								  struct s_icmp_packet pkt);
int						receive_icmp(int sck, struct sockaddr_in sa,
									 struct s_icmp_packet *pkt);

int		ping(int sck, struct sockaddr_in sa, char *address, char *ip);


char	*generate_icmp_data();

#endif
