/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 20:40:33 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/15 20:40:36 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SOUNDS_H
# define __SOUNDS_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_audio.h>
# include <unistd.h>

# define OK 	"ok.wav"
# define NOK	"nok.wav"

void	my_audio_callback(void *userdata, Uint8 *stream, int len);
void	load_wav_to_buffer(char *track);
void	play_wav_track(SDL_AudioSpec *wav_spec);
void	sound(char *track);
#endif
