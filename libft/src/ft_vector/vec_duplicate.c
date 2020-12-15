/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:06:42 by gmelisan          #+#    #+#             */
/*   Updated: 2019/03/10 18:09:15 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

t_vector	vec_duplicate(t_vector vec)
{
	t_vector new;

	new = vec_create(vec.len, vec.size);
	ft_memcpy(new.v, vec.v, vec.len * vec.size);
	return (new);
}
