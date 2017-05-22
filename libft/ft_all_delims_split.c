/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_delims_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:33:22 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/20 21:47:08 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*
**	RETURNS LENGTH OF CONTINIOUS SEQUENCE OF CHARS THAT ARE NOT DELIMETERS
**	'\n', '\t', '\r', ' ', '\f', '\v'
*/

static int		word_len_in_str(char *string, int (*compare)(int))
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = string;
	while (!compare(*ptr) && *ptr)
	{
		len++;
		ptr++;
	}
	return (len);
}

/*
**	RETURNS NUMBER OF WORDS IN A STRING DELIMITED BY
**	 '\n', '\t', '\r', ' ', '\f', '\v'
*/

static int		count_words_in_string(char *string, int (*compare)(int))
{
	char	*ptr;
	int		words;

	ptr = string;
	words = 0;
	if (string)
	{
		while (*ptr)
		{
			if (!compare(*ptr))
			{
				words++;
				ptr += word_len_in_str(ptr, compare);
				continue ;
			}
			ptr++;
		}
	}
	return (words);
}

/*
**	SPLITS A STRING BY '\n', '\t', '\r', ' ', '\f', '\v'
**	AND RETURNS AN ARRAY OF STRINGS
*/

char			**all_delims_split(char *string, int (*compare)(int))
{
	char	*s;
	char	**new;
	int		i;
	int		words;

	s = string;
	i = 0;
	words = count_words_in_string(string, compare);
	if (words == 0)
		return ((char**)NULL);
	new = (char**)malloc(sizeof(char*) * (words + 1));
	new[words] = NULL;
	while (*s && i < words)
	{
		if (!compare(*s))
		{
			new[i++] = ft_strsub(s, 0, word_len_in_str(s, compare));
			s += word_len_in_str(s, compare);
			continue ;
		}
		s++;
	}
	return (new);
}

/*
**	JUST UNCOMMENT IT TO CHECK all_delims_split() FUNCTION
**
** int		main(void)
** {
** 	char	**ptr;
** 	char	*str;
**
**	str = "\v\v\t\n\naaaasdfdsagadgd \t\v\nwojskf \nsdfsadfd sd  \0  dghfghgf ";
** 	printf("there are %d words\n", count_words_in_string(str));
** 	ptr = all_delims_split(str);
** 	while (*ptr != NULL)
** 	{
** 		printf("%s\n", *ptr);
** 		ptr++;
** 	}
** }
}*/
