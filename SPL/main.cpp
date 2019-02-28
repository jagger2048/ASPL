﻿
//#include <iostream>
#include <stdio.h>
#include <stdint.h>

//#include "frame.h"
//#include "stream.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "wavfile.h"
#include "dr_wav.h"



#include "limiter.h"
int main()
{
	printf("This is the signal processing library test case.\n");
	WAV *wavfile = wavfile_create();
	wavfile = wavfile_read("limit .wav");

	RmsLimiter* limiter = RmsLimiter_create(
											-18,	//T
											5,	// ratio
											1,	// kneeWidth
											0.05,//at
											0.2,//rt
											0,// makeup gain
											wavfile->sampleRate	);
	float* output = (float*)malloc(sizeof(float) * wavfile->totalPCMFrameCount);
	//for (size_t n = 0; n < wavfile->totalPCMFrameCount; n++)
	float tmp = 0;
	//for (size_t n = 0; n < wavfile->totalPCMFrameCount; n++)
	for (size_t n = 0; n < wavfile->totalPCMFrameCount; n++)
	{
		tmp = RmsLimiter_process(limiter, wavfile->pDataFloat[0][n], output[n]);
		//tmp = RmsLimiter_process(limiter, 0.4, output[n]);
		//printf(" %f -- %f \n", wavfile->pDataFloat[0][n], output[n]);
	}
	wavfile_write_f32("limit2 .wav", &output, wavfile->totalPCMFrameCount, 1, wavfile->sampleRate);
	wavfile_destory(wavfile);

	free(output);
	return 0;
}


/*
	spl_frame_st *pFrame = spl_frame_new(48000, 1024);

	spl_stream_st *pStream = NULL;
	pStream = audio_stream_open("music_48k_32bit.wav");

	pcm_stream_frame_get(pStream,pFrame, 1024);
	for (size_t n = 0; n < 1024; n++)
	{
		printf("%d -- %f || %d -- %f\n",
			pFrame->sample_s16[0][n],
			pFrame->sample_f32[0][n],
			pFrame->sample_s16[1][n],
			pFrame->sample_f32[0][n]);
	}
	printf("test 2");
	audio_stream_close(pStream);
*/