/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoppa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 04:43:37 by jucoppa           #+#    #+#             */
/*   Updated: 2017/12/02 07:10:04 by jucoppa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			o_len(int option, int add)
{
	static int	octet;

	octet = 0;
	if (add == -1)
		octet = -1;
	if (octet != -1)
	{
		if (option == 1)
			octet = octet + add;
		if (option == 0)
		{
			add = octet + add;
			octet = 0;
			return (add);
		}
	}
	return (octet);
}

static void	fuck_the_norm(t_join *lst, wint_t wint)
{
	char	str[5];

	str[0] = (((wint & 0x1c0000) >> 18) + 0xF0);
	str[1] = (((wint & 0x03F000) >> 6) + 0x80);
	str[2] = (((wint & 0x003F) >> 6) + 0x80);
	str[3] = ((wint & 0x003F) + 0x80);
	str[4] = '\0';
	lst->str = ft_strjoin_nfree(lst->str, str, 1);
}

void		check_wchar(t_join *lst, wint_t wint)
{
	char	str[5];

	if (wint <= 0x7F && __mb_cur_max >= 1)
	{
		str[0] = wint;
		str[1] = '\0';
		lst->str = ft_strjoin_nfree(lst->str, str, 1);
	}
	else if (wint <= 0x7FF && __mb_cur_max >= 2)
	{
		str[0] = (((wint & 0x07c0) >> 6) + 0xc0);
		str[1] = ((wint & 0x003F) + 0x80);
		str[2] = '\0';
		lst->str = ft_strjoin_nfree(lst->str, str, 1);
	}
	else if (wint <= 0xFFFF && __mb_cur_max >= 3)
	{
		str[0] = (((wint & 0xF000) >> 12) + 0xE0);
		str[1] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[2] = ((wint & 0x003F) + 0x80);
		str[3] = '\0';
		lst->str = ft_strjoin_nfree(lst->str, str, 1);
	}
	else if (wint <= 0x10FFFF && __mb_cur_max >= 4)
		fuck_the_norm(lst, wint);
}
