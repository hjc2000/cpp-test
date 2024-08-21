#pragma once
#include <stdint.h>
#include <string>

class Servo
{
private:
    double _last_feedback_position = 0;
    double _feedback_position = 0;

public:
    void Disable();
    void Enable();

    /// @brief 伺服版本。
    /// @return
    int Version();

    /// @brief 刷新伺服的反馈位置信息。
    void RefreshFeedbackPosition();

    /// @brief 伺服当前的反馈位置。有正负。
    /// @return
    int64_t FeedbackPosition();

    /// @brief 伺服上次的反馈位置。
    /// @return
    int64_t LastFeedbackPosition();

    /// @brief 伺服反馈速度。有正负。
    /// @return
    double FeedbackSpeed();

    /// @brief 逆时针方向是正向
    /// @return
    bool CounterClockwiseIsForward();

    /// @brief 设置电机的转速。这里是速率，没有方向，只能为正数。
    /// @param value
    void SetSpeed(double value);
};

class ServoFan
{
public:
    void TurnOn()
    {
    }

    void TurnOff()
    {
    }
};
