#include <android/log.h>

#include <jni.h>

#include <stdio.h>

#define MA_NO_DECODING
#define MA_NO_ENCODING
// #define MA_NO_AAUDIO
#define MA_NO_OPENSL
#define MINIAUDIO_IMPLEMENTATION

#include "miniaudio.h"

#include <stdio.h>

#define DEVICE_FORMAT ma_format_f32
#define DEVICE_CHANNELS 2
#define DEVICE_SAMPLE_RATE 48000

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput,
                   ma_uint32 frameCount) {
  ma_waveform *pSineWave;

  pSineWave = (ma_waveform *)pDevice->pUserData;

  ma_waveform_read_pcm_frames(pSineWave, pOutput, frameCount, NULL);

  (void)pInput; /* Unused. */
}

ma_waveform sineWave;
ma_device_config deviceConfig;
ma_device device;
ma_waveform_config sineWaveConfig;

bool single_init = false;

JNIEXPORT void JNICALL
Java_fr_gungun974_androidminiaudioglitchonwakeuptest_MyNativeLib_init(
    JNIEnv *env, jobject thiz) {

  if (single_init) {
    return;
  }

  single_init = true;

  deviceConfig = ma_device_config_init(ma_device_type_playback);
  deviceConfig.playback.format = DEVICE_FORMAT;
  deviceConfig.playback.channels = DEVICE_CHANNELS;
  deviceConfig.sampleRate = DEVICE_SAMPLE_RATE;
  deviceConfig.dataCallback = data_callback;
  deviceConfig.pUserData = &sineWave;

  if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
    printf("Failed to open playback device.\n");
    return;
  }

  printf("Device Name: %s\n", device.playback.name);

  sineWaveConfig = ma_waveform_config_init(
      device.playback.format, device.playback.channels, device.sampleRate,
      ma_waveform_type_sine, 0.2, 220);
  ma_waveform_init(&sineWaveConfig, &sineWave);

  if (ma_device_start(&device) != MA_SUCCESS) {
    printf("Failed to start playback device.\n");
    ma_device_uninit(&device);
    return;
  }
}
