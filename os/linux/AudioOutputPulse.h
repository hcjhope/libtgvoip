//
// libtgvoip is free and unencumbered public domain software.
// For more information, see http://unlicense.org or the UNLICENSE file
// you should have received with this source code distribution.
//

#ifndef LIBTGVOIP_AUDIOOUTPUTPULSE_H
#define LIBTGVOIP_AUDIOOUTPUTPULSE_H

#include "../../audio/AudioOutput.h"
#include "../../threading.h"
#include <pulse/pulseaudio.h>

namespace tgvoip{
namespace audio{

class AudioOutputPulse : public AudioOutput{
public:
	AudioOutputPulse(std::string devID);
	virtual ~AudioOutputPulse();
	virtual void Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels);
	virtual void Start();
	virtual void Stop();
	virtual bool IsPlaying();
	virtual void SetCurrentDevice(std::string devID);
	static bool EnumerateDevices(std::vector<AudioOutputDevice>& devs);
	static bool IsAvailable();

private:
	static void ContextStateCallback(pa_context* context, void* arg);
	static void ContextStateCallbackEnum(pa_context* context, void* arg);
	static void StreamStateCallback(pa_stream* s, void* arg);
	static void StreamSuccessCallback(pa_stream* stream, int success, void* userdata);
	static void StreamWriteCallback(pa_stream* stream, size_t requested_bytes, void* userdata);
	static void DeviceEnumCallback(pa_context* ctx, const pa_sink_info* info, int eol, void* userdata);
	void StreamWriteCallback(pa_stream* stream, size_t requestedBytes);

	pa_threaded_mainloop* mainloop;
	pa_mainloop_api* mainloopApi;
	pa_context* context;
	pa_stream* stream;

	bool isPlaying;
	bool isConnected;
	bool didStart;
	bool isLocked;
	unsigned char remainingData[10240];
	size_t remainingDataSize;
};

}
}

#endif //LIBTGVOIP_AUDIOOUTPUTPULSE_H
