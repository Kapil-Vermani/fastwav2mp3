#ifndef LAME_SETTINGS_H
#define LAME_SETTINGS_H
enum class EncodeMode
{
	AVERAGE_BIT_RATE,
	CONSTANT_BIT_RATE,
	VARIABLE_BIT_RATE
};

enum class EncodeChannel
{
	MONO,
	STEREO
};

enum bitrate_e
{
	BR_8kbps = 8,
	BR_16kbps = 16,
	BR_24kbps = 24,
	BR_32kbps = 32,
	BR_40kbps = 40,
	BR_48kbps = 48,
	BR_56kbps = 56,
	BR_64kbps = 64,
	BR_80kbps = 80,
	BR_96kbps = 96,
	BR_112kbps = 112,
	BR_128kbps = 128,
	BR_144kbps = 144,
	BR_160kbps = 160,
	BR_192kbps = 192,
	BR_224kbps = 224,
	BR_256kbps = 256,
	BR_320kbps = 320
};

enum samplerate_e
{
	SR_8khz = 8000,
	SR_11khz = 11025,
	SR_12khz = 12000,
	SR_16khz = 16000,
	SR_22khz = 22050,
	SR_24khz = 24000,
	SR_32khz = 32000,
	SR_44khz = 44100,
	SR_48khz = 48000
};

struct Settings
{
	const char* title;
	const char* artist;
	const char* album;
	const char* comment;
	const char* year;
	const char* track;
	const char* genre;
	const char* albumart;

	EncodeChannel channels;
	bitrate_e abr_bitrate;
	bitrate_e cbr_bitrate;
	int quality;
	EncodeMode enc_mode;
	samplerate_e resample_frequency;
	samplerate_e in_samplerate;

	//The constructor; used to set default values
	Settings()
	{
		//Setting the default values
		title = "";
		artist = "";
		album = "";
		comment = "";
		year = "";
		track = "";
		genre = "";
		albumart = NULL;

		channels = EncodeChannel::STEREO;
		abr_bitrate = BR_128kbps;
		cbr_bitrate = BR_128kbps;
		quality = 5;
		enc_mode = EncodeMode::CONSTANT_BIT_RATE;
		resample_frequency = SR_44khz;
		in_samplerate = SR_44khz;
	}
};
#endif
