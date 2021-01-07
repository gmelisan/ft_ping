/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:30:07 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/07 22:59:15 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/ip_icmp.h>
#include <signal.h>
#include "ft_ping.h"
#include "ft_getopt.h"

struct s_global	g_g;

static int		print_help(int ret)
{
	ft_putendl("Usage");
	ft_putendl("  ping [options] <destination>\n");
	ft_putendl("Options:");
	ft_printf("  %-20s%s\n", "<destinations>", "dns name or ip address");
	ft_printf("  %-20s%s\n", "-c [count]", "stop after sending 'count' "
											"packets. Default 0 (infinite)");
	ft_printf("  %-20s%s\n", "-D", "print timestamps");
	ft_printf("  %-20s%s\n", "-h", "print help and exit");
	ft_printf("  %-20s%s\n", "-i [interval]", "set inteval between pings (default 1)");
	ft_printf("  %-20s%s\n", "-q", "quiet mode: nothing is displayed except "
									"summary lines");
	ft_printf("  %-20s%s\n", "-t [TTL]", "set time to live value");
	ft_printf("  %-20s%s\n", "-v", "verbose mode with additional messages");
	ft_printf("  %-20s%s\n", "-V", "print version and exit");
	exit(ret);
	return (0);
}

static int		enable_option(char o)
{
	if (o == 'c')
		g_g.options.c = ft_atoi(g_optarg);
	else if (o == 'D')
		g_g.options.D = 1;
	else if (o == 'i')
		g_g.options.i = ft_atoi(g_optarg);
	else if (o == 't')
		g_g.options.t = ft_atoi(g_optarg);
	else if (o == 'v')
		g_g.options.v = 1;
	else if (o == 'q')
		g_g.options.q = 1;
	return (0);
}

static int		parse_options(int argc, char **argv)
{
	int c;

	g_g.options.t = DEFAULT_TTL;
	g_g.options.i = DEFAULT_INTERVAL;
	while ((c = ft_getopt(argc, argv, "c:Dhi:qt:vV")) != -1)
	{
		if (c == 'h')
			print_help(0);
		else if (c == 'c' || c == 'v' || c == 'D' || c == 'q' || c == 't' ||
					c == 'i')
			enable_option(c);
		else if (c == 'V')
		{
			ft_putendl("ping implementation by gmelisan");
			exit(0);
		}
		else if (c == '?')
			print_help(2);
		else
			return (-1);
	}
	return (0);
}

int				open_socket()
{
	int sck;
	struct timeval tv_out;
	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;
	
	sck = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); // need CAP_NET_RAW
	if (sck < 0)
	{
		fatal("Can't open socket: %s%s", strerror(errno),
				getuid() != 0 ? " (try use sudo)" : "");
	}
	if (setsockopt(sck, SOL_IP, IP_TTL, &g_g.options.t, sizeof(g_g.options.t)) < 0)
		fatal("Can't setup socket (ttl): %s", strerror(errno));
	if (setsockopt(sck, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv_out, sizeof(tv_out)) < 0)
		fatal("Can't setup socket (timeout): %s", strerror(errno));
	return (sck);
}

int				main(int argc, char **argv)
{
	char str[100];

	if (parse_options(argc, argv) == -1)
		return 1;
	if (g_optind >= argc)
		fatal("usage error: Destination address required");
	if (g_g.options.i <= 0)
		fatal("Interval must be > 0");
	resolve4(argv[g_optind], &g_g.sa);
	inet_ntop(AF_INET, &g_g.sa.sin_addr, str, 100);
	g_g.address_s = argv[g_optind];
	g_g.ip_s = str;
	g_g.sck = open_socket();
	ft_printf("PING %s (%s) %d(%d) bytes of data.\n", argv[g_optind], str,
			  ICMP_DATA_SIZE, ICMP_PACKET_SIZE + IP_HEADER_SIZE);
	return (ping());
}
