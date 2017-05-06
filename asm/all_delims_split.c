/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_delims_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:33:22 by rvolovik          #+#    #+#             */
/*   Updated: 2017/05/06 15:04:21 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "byte_code_header.h"

static int		word_len_in_str(char *string)
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = string;
	while (!ft_isspace(*ptr))
	{
		len++;
		ptr++;
	}
	return (len);
}

static int		count_words_in_string(char *string)
{
	char	*ptr;
	int		words;

	ptr = string;
	words = 0;
	if (string)
	{
		while (*ptr)
		{
			if (!ft_isspace(*ptr))
			{
				words++;
				ptr += word_len_in_str(ptr);
				continue ;
			}
			ptr++;
		}
	}
	return (words);
}

char			**all_delims_split(char *string)
{
	char	*s;
	char	**new;
	int		i;
	int		words;

	s = string;
	i = 0;
	words = count_words_in_string(string);
	if (words == 0)
		return ((char**)NULL);
	new = (char**)malloc(sizeof(char*) * (words + 1));
	new[words] = NULL;
	while (*s && i < words)
	{
		if (!ft_isspace(*s))
		{
			new[i++] = ft_strsub(s, 0, word_len_in_str(s));
			s += word_len_in_str(s);
			continue ;
		}
		s++;
	}
	return (new);
}

int		main(void)
{
	char	**ptr;
	char	*str = "\v\v\t\n\naaaasdfdsagadgd \t\v\nwojskf \nsdfsadfd sd  \0  dghfghgf ";

	printf("there are %d words\n", count_words_in_string(str));
	ptr = all_delims_split(str);
	while (*ptr != NULL)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
}
