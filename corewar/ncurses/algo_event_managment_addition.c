/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_event_managment_addition.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkosolap <dkosolap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:29:57 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/06/06 19:49:52 by dkosolap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualisation.h"

void	extend_key_event(int c)
{
	if (c == '1')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 2;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '2')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 5;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '3')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 10;
		pthread_mutex_unlock(&g_mutex_sec);
	}
	if (c == '0')
	{
		pthread_mutex_lock(&g_mutex_sec);
		g_sec = 0;
		pthread_mutex_unlock(&g_mutex_sec);
	}
}

void	extend_key_event_2(int c)
{
	if (c == 'p')
	{
		pthread_mutex_lock(&g_mutex_flag);
		g_mus ^= P_MUS;
		pthread_mutex_unlock(&g_mutex_flag);
	}
	if (c == ' ')
	{
		pthread_mutex_lock(&g_mutex_flag);
		g_flag ^= A_STOP;
		pthread_mutex_unlock(&g_mutex_flag);
	}
	if (c == 's')
	{
		pthread_mutex_lock(&g_mutex_flag);
		g_flag |= STEP;
		pthread_mutex_unlock(&g_mutex_flag);
	}
}

void	stop(short *tmp_flag, t_init_screen *init)
{
	*tmp_flag = (((short)tmp_flag << 8) | g_sec) | g_mus;
	pthread_mutex_unlock(&g_mutex_flag);
	while (1)
	{
		usleep(3 * 100000);
		pthread_mutex_lock(&g_mutex_sec);
		if (*tmp_flag != ((((short)tmp_flag << 8) | g_sec) | g_mus))
		{
			update_while_paused(init);
			*tmp_flag = (((short)tmp_flag << 8) | g_sec) | g_mus;
		}
		pthread_mutex_unlock(&g_mutex_sec);
		pthread_mutex_lock(&g_mutex_flag);
		if ((g_flag & EXIT) || !(g_flag & A_STOP) || (g_flag & STEP))
			break ;
		pthread_mutex_unlock(&g_mutex_flag);
		usleep(3 * 100000);
	}
}
