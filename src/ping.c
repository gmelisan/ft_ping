/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:58:29 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/06 22:14:22 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		ping(int sck, struct sockaddr_in sa, char *address, char *ip)
{
	struct s_icmp_packet pkt;
	int ret;
	int seq;

	seq = 1;
	info("g_options.c = %d", g_options.c);
	while (!g_options.exit_flag) {
		pkt = create_icmp(seq, getpid(), generate_icmp_data());
		send_icmp(sck, sa, pkt);
		ret = receive_icmp(sck, sa, &pkt);
		info("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=? ms",
			 ret, address, ip, seq, g_options.t);
		if (g_options.c && seq == g_options.c)
			break ;
		++seq;
		sleep(g_options.i); // I have no sleep lol
	}
	info("----");
	info("statistics");
	return (0);
}

