/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:29:46 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/08 16:00:56 by gmelisan         ###   ########.fr       */
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
# include <signal.h>
# include <sys/time.h>
# include "libft.h"

# define DEFAULT_TTL			250
# define ICMP_PACKET_SIZE		64
# define ICMP_DATA_SIZE			(ICMP_PACKET_SIZE - ICMP_MINLEN)
# define IP_HEADER_SIZE			20
# define RECV_TIMEOUT			1
# define DEFAULT_INTERVAL		1

# define UCHAR					unsigned char
# define USHORT					unsigned short
# define UINT					unsigned int

struct							s_options
{
	int							c;
	int							d_big;
	int							i;
	int							t;
	int							v;
	int							q;
};

extern struct					s_global
{
	struct s_options			options;
	int							sck;
	char						*address_s;
	char						*ip_s;
	struct sockaddr_in			sa;
	struct timeval				one_packet_time;
	struct timeval				full_time;
	int							transmitted;
	int							received;
	double						rtt_min;
	double						rtt_max;
	double						rtt_total;
}								g_g;

struct							s_icmp_packet
{
	struct icmphdr				header;
	UCHAR						data[ICMP_DATA_SIZE];
};

int								info(const char *fmt, ...);
int								error(const char *fmt, ...);
void							fatal(const char *fmt, ...);
void							resolve4(const char *dst,
											struct sockaddr_in *out);
void							resolve6(const char *dst,
											struct sockaddr_in6 *out);

struct s_icmp_packet			create_icmp(int seq, int id, char *data);
int								send_icmp(int sck, struct sockaddr_in sa,
									struct s_icmp_packet pkt);
int								receive_icmp(int sck, struct sockaddr_in sa,
									struct s_icmp_packet *pkt);
int								check_icmps(const struct s_icmp_packet *send,
									const struct s_icmp_packet *receive);

int								open_socket(void);
int								ping(void);
void							print_stat_and_exit(void);
char							*generate_icmp_data(void);
void							timer_start(struct timeval *start_time);
double							timer_stop(const struct timeval *start_time);

#endif
