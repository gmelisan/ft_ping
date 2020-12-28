/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:30:07 by gmelisan          #+#    #+#             */
/*   Updated: 2020/12/15 21:29:44 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/ip_icmp.h>
#include "ft_ping.h"
#include "ft_getopt.h"

struct s_options	g_options;

static int		print_help(int ret)
{
	ft_putendl("Usage");
	ft_putendl("  ping [options] <destination>\n");
	ft_putendl("Options:");
	ft_printf("  %-20s%s\n", "<destinations>", "dns name or ip address");
	ft_printf("  %-20s%s\n", "-D", "print timestamps");
	ft_printf("  %-20s%s\n", "-h", "print help and exit");
	ft_printf("  %-20s%s\n", "-v", "verbose");
	ft_printf("  %-20s%s\n", "-V", "print version and exit");
	exit(ret);
	return (0);
}

static int		enable_option(char o)
{
	if (o == 'v')
		g_options.v = 1;
	else if (o == 'D')
		g_options.D = 1;
	else if (o == 't')
		g_options.t = ft_atoi(g_optarg);
	return (0);
}

static int		parse_options(int argc, char **argv)
{
	int c;

	while ((c = ft_getopt(argc, argv, "ht:vV")) != -1)
	{
		if (c == 'h')
			return (print_help(0));
		else if (c == 'v' || c == 'D')
			return (enable_option(c));
		else if (c == 'V')
		{
			ft_putendl("ping implementation by gmelisan");
			exit(0);
		}
		else if (c == '?')
			return (print_help(2));
		else
			return (-1);
	}
	return (0);
}

ushort get_checksum(void *b, int len)
{
    ushort *buf;
    uint sum;
    ushort result;

	buf = (ushort *)b;
	sum = 0;
    while (len > 1)
	{
        sum += *buf++;
		len -= 2;
	}
    if (len == 1)
        sum += *(uchar*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int				send_icmp(int sck, struct sockaddr_in sa)
{
	struct s_icmp_packet	pkt;
	ssize_t ret;

	pkt.header.type = ICMP_ECHO;
	pkt.header.code = 0;
	pkt.header.un.echo.sequence = (ushort)1;
	pkt.header.un.echo.id = (ushort)getpid();
	memset(pkt.data, 'a', sizeof(pkt.data));
	pkt.header.checksum = get_checksum(&pkt, sizeof(pkt));
	ret = sendto(sck, &pkt, sizeof(pkt), 0, (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0)
		return (die("sendto(): %s", strerror(errno)));
	if (ret < ICMP_PACKET_SIZE)
		return (die("sendto(): sended incomplete data"));
	ft_printf("send: type %d, code %d, id %d, seq %d, data %s\n",
			  pkt.header.type, pkt.header.code, pkt.header.un.echo.id,
			  pkt.header.un.echo.sequence, pkt.data);
	return (0);
}

int				receive_icmp(int sck)
{
	struct s_icmp_packet	*pkt;
	struct sockaddr_in		sa;
	socklen_t				from_len;
	char					*ptr;
	ssize_t					ret;

	ptr = (char *)malloc(sizeof(char) * (sizeof(pkt) + 20));
	ret = recvfrom(sck, ptr, sizeof(pkt) + 20, 0, (struct sockaddr*)&sa, &from_len);
	if (ret < 0)
		return (die("recvfrom(): %s", strerror(errno)));
	ft_printf("ret = %d\n", ret);
	ptr += 20;
	pkt = (struct s_icmp_packet *)ptr;
	ft_printf("rcv: type %d, code %d, id %d, seq %d, data %s\n",
			  pkt->header.type, pkt->header.code, pkt->header.un.echo.id,
			  pkt->header.un.echo.sequence, pkt->data);
	return (0);
}

int				main(int argc, char **argv)
{
	g_options.t = DEFAULT_TTL;
	if (parse_options(argc, argv) == -1)
		return 1;
	if (optind >= argc)
		return (die("usage error: Destination address required"));

	struct sockaddr_in sa;
	char str[100];
	
	resolve4(argv[optind], &sa);
	inet_ntop(AF_INET, &sa.sin_addr, str, 100);
	//ft_printf("%s\n", str);
	int sck = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); // need CAP_NET_RAW
	if (sck < 0)
		return (die("socket(): %s", strerror(errno)));
	send_icmp(sck, sa);
	receive_icmp(sck);
	return (0);
}
