/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:58:29 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/08 17:11:52 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	save_rtt(double elapsed)
{
	if (g_g.rtt_min < 0 || elapsed < g_g.rtt_min)
		g_g.rtt_min = elapsed;
	if (g_g.rtt_max < 0 || elapsed > g_g.rtt_max)
		g_g.rtt_max = elapsed;
	g_g.rtt_total += elapsed;
}

static void	print_message(int ret, int seq, double elapsed)
{
	if (ft_strequ(g_g.address_s, g_g.ip_s))
		info("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms",
				ret, g_g.ip_s, seq, g_g.options.t, elapsed);
	else
		info("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms",
				ret, g_g.address_s, g_g.ip_s, seq, g_g.options.t, elapsed);
}

static void	perform_ping(int seq)
{
	struct s_icmp_packet	pkt_send;
	struct s_icmp_packet	pkt_receive;
	int						ret;
	double					elapsed;

	pkt_send = create_icmp(seq, getpid(), generate_icmp_data());
	timer_start(&g_g.one_packet_time);
	++g_g.transmitted;
	if (send_icmp(g_g.sck, g_g.sa, pkt_send) > 0)
	{
		ret = receive_icmp(g_g.sck, g_g.sa, &pkt_receive);
		elapsed = timer_stop(&g_g.one_packet_time);
		if (ret > 0 && !check_icmps(&pkt_send, &pkt_receive))
			ret = -1;
		if (ret > 0)
		{
			print_message(ret, seq, elapsed);
			save_rtt(elapsed);
			++g_g.received;
		}
	}
}

static void	sigh_alrm(int n)
{
	static int seq = 1;

	(void)n;
	close(g_g.sck);
	g_g.sck = open_socket();
	perform_ping(seq);
	if (g_g.options.c && seq == g_g.options.c)
		print_stat_and_exit();
	++seq;
	alarm(g_g.options.i);
}

int			ping(void)
{
	signal(SIGINT, sigh_int);
	signal(SIGALRM, sigh_alrm);
	g_g.rtt_min = -1;
	g_g.rtt_max = -1;
	timer_start(&g_g.full_time);
	sigh_alrm(SIGALRM);
	while (21)
		;
	return (0);
}
