/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:20:22 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:47:33 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIT_H
# define FT_BIT_H

# include <stdbool.h>

typedef union u_byte_bit
{
	char	byte;

	struct s_bitFields
	{
		bool	bit0 : 1;
		bool	bit1 : 1;
		bool	bit2 : 1;
		bool	bit3 : 1;
		bool	bit4 : 1;
		bool	bit5 : 1;
		bool	bit6 : 1;
		bool	bit7 : 1;
	} bits;
}	t_byte_bit;

typedef union u_index_bit
{
	int		data;
	struct	s_index_bit
	{
		unsigned char	bit:3;
		int				index:29;
	} bits;
}	t_index_bit;

/**  ft_byte_bit.c  **/

_Bool	ft_byte_bit_get(char *byte, int index);
_Bool	ft_byte_bit_set(char *byte, int index, _Bool value);

/**  ft_index_bit.c  **/
_Bool	ft_index_bit_get(char *data, t_index_bit index_bit);
_Bool	ft_index_bit_set(char *data, t_index_bit index_bit, _Bool value);
#endif