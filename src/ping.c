/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:58:29 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/07 22:50:02 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_stat_and_exit()
{
	double t;

	t = timer_stop(&g_g.full_time);
	ft_printf("\n");
	ft_printf("--- %s ping statistics ---\n", g_g.address_s);
	ft_printf("%d packets transmitted, %d received, ",
				g_g.transmitted, g_g.received);
	if (g_g.transmitted == g_g.received)
		ft_printf("0%% packet loss, ");
	else
		ft_printf("%.4f%% packet loss, ", (g_g.transmitted - g_g.received) * 100.0 / g_g.transmitted);
	ft_printf("time %.0fms\n", t);
	if (g_g.received)
		ft_printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n",
				  g_g.rtt_min, g_g.rtt_total / g_g.received, g_g.rtt_max);
	exit(0);
}

void	sigh_int(int n)
{
	(void)n;

	alarm(0);
	close(g_g.sck);
	print_stat_and_exit();
}

void	save_rtt(double elapsed)
{
	if (g_g.rtt_min < 0 || elapsed < g_g.rtt_min)
		g_g.rtt_min = elapsed;
	if (g_g.rtt_max < 0 || elapsed > g_g.rtt_max)
		g_g.rtt_max = elapsed;
	g_g.rtt_total += elapsed;	
}

void	sigh_alrm(int n)
{
	struct s_icmp_packet pkt_send;
	struct s_icmp_packet pkt_receive;
	int ret;
	static int seq = 1;
	double elapsed;

	(void)n;
	close(g_g.sck);
	g_g.sck = open_socket();
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
			info("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms",
				 ret, g_g.address_s, g_g.ip_s, seq, g_g.options.t, elapsed);
			save_rtt(elapsed);
			++g_g.received;
		}
	}
	if (g_g.options.c && seq == g_g.options.c)
		print_stat_and_exit();
	++seq;
	alarm(g_g.options.i);
}

int		ping()
{
	signal(SIGINT, sigh_int);
	signal(SIGALRM, sigh_alrm);
	g_g.rtt_min = -1;
	g_g.rtt_max = -1;
	timer_start(&g_g.full_time);
	sigh_alrm(SIGALRM);
	while (21);
	return (0);
}
