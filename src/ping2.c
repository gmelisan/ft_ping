/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:53:14 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/08 15:53:50 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_stat_and_exit(void)
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
		ft_printf("%.4f%% packet loss, ",
				(g_g.transmitted - g_g.received) * 100.0 / g_g.transmitted);
	ft_printf("time %.0fms\n", t);
	if (g_g.received)
		ft_printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n",
				g_g.rtt_min, g_g.rtt_total / g_g.received, g_g.rtt_max);
	exit(0);
}
