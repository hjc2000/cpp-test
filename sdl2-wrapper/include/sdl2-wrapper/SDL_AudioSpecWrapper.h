#pragma once
#include <base/string/Json.h>
#include <base/Wrapper.h>
#include <ffmpeg-wrapper/info-collection/IAudioFrameInfoCollection.h>
#include <SDL.h>
#include <sstream>
#include <string>

using std::endl;
using std::string;
using std::stringstream;
using namespace video;

namespace video
{
    class SDL_AudioSpecWrapper :
        public base::Wrapper<SDL_AudioSpec>,
        public IAudioFrameInfoCollection,
        public base::IJsonSerializable
    {
    private:
        SDL_AudioSpec _spec{};
        SDL_AudioSpec *_wrapped_obj = &_spec;

    public:
        SDL_AudioSpecWrapper() = default;
        SDL_AudioSpecWrapper(IAudioFrameInfoCollection const &infos);
        SDL_AudioSpecWrapper(IAudioStreamInfoCollection const &infos);
        SDL_AudioSpecWrapper(SDL_AudioSpecWrapper &another);
        void operator=(SDL_AudioSpecWrapper const &another);

        SDL_AudioSpec *&WrappedObj() override
        {
            throw std::runtime_error{"不支持的操作"};
        }

        SDL_AudioSpec *WrappedObj() const override
        {
            return _wrapped_obj;
        }

        base::Json ToJson() override;

#pragma region 通过 IAudioFrameInfoCollection 继承
        AVRational TimeBase() const override;
        void SetTimeBase(AVRational value) override;

        /// @brief 获取采样格式
        /// @return 如果 SDL_AudioSpec 的 format 字段内储存的 SDL 采样格式没有对应的 AVSampleFormat 值，
        /// 则会返回 AVSampleFormat::AV_SAMPLE_FMT_NONE
        AVSampleFormat SampleFormat() const override;

        /// @brief 设置采样格式
        /// @param value 如果设置的 AVSampleFormat 值没有对应的 SDL 值，则会将 SDL_AudioSpec 的 format 字段
        /// 设置为 0.
        void SetSampleFormat(AVSampleFormat value) override;

        int SampleRate() const override;
        void SetSampleRate(int value) override;

        AVChannelLayout ChannelLayout() const override;
        void SetChannelLayout(AVChannelLayout value) override;

        int SampleCount() const override;
        void SetSampleCount(int value) override;
#pragma endregion
    };
} // namespace video