/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:58:22 by gmelisan          #+#    #+#             */
/*   Updated: 2020/12/15 18:37:43 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include "libft.h"

extern char	*g_optarg;
extern int	g_optind;
extern int	g_optpos;
extern int	g_optopt;
extern int	g_opterr;
extern char	*g_opterrpref;

int			ft_getopt(int argc, char *const argv[], const char *optstring);

#endif
