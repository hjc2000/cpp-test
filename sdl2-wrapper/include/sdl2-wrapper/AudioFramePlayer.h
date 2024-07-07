#pragma once
#include <base/pipe/IConsumer.h>
#include <condition_variable>
#include <ffmpeg-wrapper/AVChannelLayoutExtension.h>
#include <ffmpeg-wrapper/container/HysteresisBlockingFrameQueue.h>
#include <ffmpeg-wrapper/pipe/SwrPipe.h>
#include <ffmpeg-wrapper/wrapper/AVFrameWrapper.h>
#include <ffmpeg-wrapper/wrapper/SwrContextWrapper.h>
#include <jccpp/TimeInterpolator.h>
#include <sdl2-wrapper/IRefTimer.h>
#include <sdl2-wrapper/SDL_DefaultAudioDevice.h>
#include <sdl2-wrapper/SDL_EventGetter.h>
#include <sdl2-wrapper/SDL_Initializer.h>

namespace video
{
	class AudioFramePlayer
		: public IDisposable,
		  public IRefTimer,
		  public base::IConsumer<AVFrameWrapper>
	{
	private:
		atomic_bool _disposed = false;
		atomic_bool _should_pause = false;
		AVFrameWrapper _swr_out_frame;
		shared_ptr<SDL_DefaultAudioDevice> _device;
		AVRational _time_base;
		shared_ptr<HysteresisBlockingFrameQueue> _frame_queue{new HysteresisBlockingFrameQueue};
		shared_ptr<SwrPipe> _swr_pipe;
		jccpp::TimeInterpolator _time_interpolator;

		void AudioCallbackHandler(uint8_t *stream, int len);

	public:
		/**
		 * @brief 要求 infos 中的 time_base 属性必须是有效的，本对象要使用此属性。
		 *
		 * @param infos
		 */
		AudioFramePlayer(IAudioStreamInfoCollection &infos);
		~AudioFramePlayer();
		void Dispose() override;

		int64_t RefTime() override;

		/**
		 * @brief 控制暂停与播放。
		 *
		 * @param pause 传入 true 表示暂停，传入 false 开始播放
		 */
		void Pause(bool pause);

		/**
		 * @brief 向播放器送入帧，也可以冲洗播放器。
		 *
		 * @param frame 送入播放器的帧。送入空指针表示冲洗播放器。
		 */
		void SendData(AVFrameWrapper &frame) override;

		void Flush() override;
	};
}
