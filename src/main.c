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

#include <arpa/inet.h>
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
	ft_printf("%s\n", str);
	return (0);
}
