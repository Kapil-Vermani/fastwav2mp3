#include "LameTask.h"
#include "AppConstants.h"
#include <iostream>
#include <sstream>

void CLameTask::setAlbumArt(lame_t gfp, char const* arg_pcFileName)
{
	std::stringstream errMsg;
	FILE *fpi = 0;
	char *albumart = 0;
	int iResult = -1;
	if (arg_pcFileName == NULL)
	{
		errMsg << "WARNING: input file name pointer is null for albumart, so we cannot set that\n";
		errorHandler(errMsg.str());
		return;
	}

	fpi = fopen(arg_pcFileName, "rb");

	if (!fpi)
	{
		iResult = 1; 
		return;

	}
	else
	{
		size_t size;		
		fseek(fpi, 0, SEEK_END);
		size = ftell(fpi);
		fseek(fpi, 0, SEEK_SET);
		albumart = (char*)malloc(size);
		if (!albumart)
		{
			iResult = 2;
		}
		else
		{
			if (fread(albumart, 1, size, fpi) != size)
			{
				iResult = 3;
			}
			else
			{
				iResult = id3tag_set_albumart(gfp, albumart, size) ? 4 : 0;
			}
			free(albumart);
		}
		fclose(fpi);
	}
	switch (iResult)
	{
		case 1:
			errMsg << "WARNING: could not open file " << arg_pcFileName << " for albumart\n";
			errorHandler(errMsg.str());
			break;
		case 2:
			errMsg << "WARNING: insufficient memory for reading the albumart.\n";
			errorHandler(errMsg.str());
			break;
		case 3:
			errMsg << "WARNING: read error in " << arg_pcFileName << " for albumart\n";
			errorHandler(errMsg.str());
			break;
		case 4:
			errMsg << "WARNING: unsupported image: " << arg_pcFileName << " for albumart. Specify JPEG/PNG/GIF image\n";
			errorHandler(errMsg.str());
			break;
		default:
			break;
	}
}

void CLameTask::operator()()
{
	std::stringstream errMsg;
	lame_global_flags*	gfp = NULL;
	gfp = lame_init();
	lame_set_in_samplerate(gfp, m_cSettings.in_samplerate);

	//Init the id3 tag structure
	id3tag_init(gfp);
	id3tag_v2_only(gfp);
	id3tag_set_year(gfp, m_cSettings.year);
	id3tag_set_genre(gfp, m_cSettings.genre);
	id3tag_set_artist(gfp, m_cSettings.artist);
	id3tag_set_album(gfp, m_cSettings.album);
	id3tag_set_title(gfp, m_cSettings.title);
	id3tag_set_track(gfp, m_cSettings.track);
	id3tag_set_comment(gfp, m_cSettings.comment);
	if (m_cSettings.albumart != NULL)
	{
		setAlbumArt(gfp, m_cSettings.albumart);
	}

	//Setting Channels
	switch (m_cSettings.channels)
	{
	case EncodeChannel::MONO:
		lame_set_mode(gfp, MONO);
		lame_set_num_channels(gfp, 1);
		break;
	case EncodeChannel::STEREO:
		lame_set_mode(gfp, JOINT_STEREO);
		lame_set_num_channels(gfp, 2);
		break;
	}


	//VbrTag
	lame_set_bWriteVbrTag(gfp, 1);
	switch (m_cSettings.enc_mode)
	{
	case EncodeMode::AVERAGE_BIT_RATE:
	{
		int i = m_cSettings.abr_bitrate;
		if (i >= 8000)
		{
			i = (i + 500) / 1000;
		}
		if (i > 320)
		{
			i = 320;
		}
		if (i < 8)
		{
			i = 8;
		}
		lame_set_VBR(gfp, vbr_abr);
		lame_set_VBR_mean_bitrate_kbps(gfp, i);
	}
	break;
	case EncodeMode::CONSTANT_BIT_RATE:
		lame_set_VBR(gfp, vbr_off);
		lame_set_quality(gfp, m_cSettings.quality);
		lame_set_brate(gfp, m_cSettings.cbr_bitrate);
		break;
	case EncodeMode::VARIABLE_BIT_RATE:
		lame_set_VBR(gfp, vbr_mtrh);
		lame_set_VBR_q(gfp, m_cSettings.quality);
		break;
	}

	lame_set_out_samplerate(gfp, m_cSettings.resample_frequency);

	lame_set_findReplayGain(gfp, 1);
	lame_set_write_id3tag_automatic(gfp, 0); //Dont write id3tag, will write it myself

	if (lame_init_params(gfp) == -1)
	{
		errorHandler("FATAL ERROR: parameters failed to initialize properly in lame. Aborting!\n");
		return;
	}
	else
	{
		int read = 0;
		int	write = 0;
		long PCM_total_size = 0;
		long cumulative_read = 0;

		FILE *pcm = fopen(m_sInputFileName.c_str(), "rb");
		FILE *mp3 = fopen(m_sOutputFileName.c_str(), "wb");

		if (pcm == NULL)
		{
			errMsg << "FATAL ERROR: file "<< m_sInputFileName<<"can't be open for read. Aborting!\n";
			errorHandler(errMsg.str());
			return;
		}
		fseek(pcm, 0, SEEK_END);
		PCM_total_size = ftell(pcm);
		fseek(pcm, 0, SEEK_SET);

		if (mp3 == NULL)
		{
			errMsg << "FATAL ERROR: file " << m_sOutputFileName<< "can't be open for write. Aborting!\n";
			errorHandler(errMsg.str());
			return;
		}

		unsigned char* buffer = new unsigned char[LAME_MAXMP3BUFFER];

		short int pcm_buffer[PCM_SIZE * 2];
		unsigned char mp3_buffer[MP3_SIZE];


		int imp3 = lame_get_id3v2_tag(gfp, buffer, LAME_MAXMP3BUFFER);
		fwrite(buffer, sizeof(char), imp3, mp3);//write the id3v2 tag
		long audio_pos = ftell(mp3); //store beginning of audio data


		do
		{
			read = fread(pcm_buffer, 2 * sizeof(short int), PCM_SIZE, pcm);
			cumulative_read += (long)read * 2 * sizeof(short int);
			if (read == 0)
			{
				write = lame_encode_flush(gfp, mp3_buffer, MP3_SIZE);
			}
			else
			{
				write = lame_encode_buffer_interleaved(gfp, pcm_buffer, read, mp3_buffer, MP3_SIZE);
			}
			fwrite(mp3_buffer, write, sizeof(char), mp3);

		} while (read != 0);

		imp3 = lame_get_id3v1_tag(gfp, buffer, LAME_MAXMP3BUFFER);
		fwrite(buffer, sizeof(char), imp3, mp3);

		imp3 = lame_get_lametag_frame(gfp, buffer, LAME_MAXMP3BUFFER);
		if (fseek(mp3, audio_pos, SEEK_SET) != 0)
		{
			errorHandler("WARNING: can't seek back to update LAME-tag frame!\n");
		}
		fwrite(buffer, sizeof(char), imp3, mp3);
		delete[] buffer;

		fclose(mp3);
		fclose(pcm);
	}

	lame_close(gfp);

}

void CLameTask::errorHandler(const std::string& msg)
{
	std::cerr << msg << std::endl;
}

