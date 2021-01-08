/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:52:19 by gmelisan          #+#    #+#             */
/*   Updated: 2021/01/08 15:55:42 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	timer_start(struct timeval *start_time)
{
	if (start_time)
		gettimeofday(start_time, NULL);
}

double	timer_stop(const struct timeval *start_time)
{
	struct timeval	current_time;
	double			ms;

	if (!start_time)
		return (-1);
	gettimeofday(&current_time, NULL);
	current_time.tv_sec -= start_time->tv_sec;
	current_time.tv_usec -= start_time->tv_usec;
	ms = current_time.tv_sec * 1000.0;
	ms += current_time.tv_usec / 1000.0;
	return (ms);
}
