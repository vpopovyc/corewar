/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkrutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:08:39 by mkrutik           #+#    #+#             */
/*   Updated: 2016/11/29 15:57:09 by mkrutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *src1, const char *src2)
{
	unsigned char *s1;
	unsigned char *s2;

	s1 = (unsigned char*)src1;
	s2 = (unsigned char*)src2;
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
