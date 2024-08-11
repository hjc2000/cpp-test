#pragma once
#include <base/container/HysteresisBlockingQueue.h>
#include <base/IDisposable.h>
#include <base/pipe/IConsumer.h>
#include <sdl2-wrapper/AudioPacketPlayer.h>
#include <sdl2-wrapper/VideoPacketPlayer.h>

namespace video
{
    /// <summary>
    ///		同时播放一路流的音频包和一路流的视频包。
    /// </summary>
    class AVPacketPlayer final :
        public base::IDisposable,
        public base::IConsumer<AVPacketWrapper>
    {
    public:
        /// <summary>
        ///
        /// </summary>
        /// <param name="x">窗口横坐标</param>
        /// <param name="y">窗口纵坐标</param>
        /// <param name="video_stream">要播放的视频流</param>
        /// <param name="audio_stream">要播放的音频流</param>
        AVPacketPlayer(int x, int y, AVStreamWrapper &video_stream, AVStreamWrapper &audio_stream);
        ~AVPacketPlayer();
        void Dispose() override;

    private:
        atomic_bool _disposed = false;
        shared_ptr<VideoPacketPlayer> _video_packet_player;
        shared_ptr<AudioPacketPlayer> _audio_packet_player;
        int _video_stream_index = 0;
        int _audio_stream_index = 0;

    public:
        void Pause(bool pause);
        void SendData(AVPacketWrapper &packet) override;

        void Flush() override
        {
            _video_packet_player->Flush();
            _audio_packet_player->Flush();
        }
    };

    void test_AVPacketPlayer();
} // namespace video
