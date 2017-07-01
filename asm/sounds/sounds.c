/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 20:39:55 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/15 20:40:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/sounds.h"

static Uint8		*g_audio_pos;
static Uint32		g_audio_len;

void	my_audio_callback(void *userdata, Uint8 *stream, int len)
{
	Uint32 tmp_len;

	tmp_len = len;
	if (g_audio_len == 0)
		return ;
	else if (tmp_len > g_audio_len)
		len = g_audio_len;
	userdata = NULL;
	SDL_memcpy(stream, g_audio_pos, len);
	SDL_MixAudio(stream, g_audio_pos, len, SDL_MIX_MAXVOLUME);
	g_audio_pos += len;
	g_audio_len -= len;
}

void	play_wav_track(SDL_AudioSpec *wav_spec)
{
	if (SDL_OpenAudio(wav_spec, NULL) < 0)
		return ;
	else
	{
		SDL_PauseAudio(0);
		while (g_audio_len > 0)
			SDL_Delay(100);
	}
}

void	load_wav_to_buffer(char *track)
{
	static Uint8			*wav_buffer;
	static Uint32			wav_length;
	static SDL_AudioSpec	wav_spec;

	if (SDL_LoadWAV(track, &wav_spec, &wav_buffer, &wav_length) == NULL)
		return ;
	else
	{
		wav_spec.callback = my_audio_callback;
		wav_spec.userdata = NULL;
		g_audio_pos = wav_buffer;
		g_audio_len = wav_length;
		play_wav_track(&wav_spec);
		SDL_CloseAudio();
		SDL_FreeWAV(wav_buffer);
	}
}

void	sound(char *track)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		SDL_Log("[SDL] Can't init SDL");
	else
		load_wav_to_buffer(track);
}
