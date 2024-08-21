#pragma once
#include <stdint.h>

/// @brief 健身模式
enum class Option_BodyBuildingMode
{
    Standard
};

enum class Option_AdditionalMode
{
    None,
};

class Option
{
private:
    Option_BodyBuildingMode _body_building_mode;
    Option_BodyBuildingMode _last_body_building_mode;

    Option_AdditionalMode _additional_mode;
    Option_AdditionalMode _last_additional_mode;

    double _tension_kg = 0;
    double _last_tension_kg = 0;

public:
    void Refresh_BodyBuildingMode();
    Option_BodyBuildingMode BodyBuildingMode();
    Option_BodyBuildingMode LastBodyBuildingMode();
    bool BodyBuildingModeChanged();

    void Refresh_AdditionalMode();
    Option_AdditionalMode AdditionalMode();
    Option_AdditionalMode LastAdditionalMode();
    bool AdditionalModeCodeChanged();

    void Refresh_Tension_kg();
    double Tension_kg();
    double LastTension_kg();
    bool Tension_kg_Changed();

    /// @brief 允许的最大拉力。
    /// @return
    double MaxTension_kg();

    /// @brief 收线速度。
    /// @return
    double WindingSpeed();

    /// @brief 转矩限制值 / 拉力_kg
    /// @note 将 拉力_kg 乘上本属性，就可得到转矩限制值。转矩限制值是个百分比。
    /// @return
    double TorqueRatio();

    /// @brief 使用引力包。
    /// @return
    bool UseGravitationPackage();

    /// @brief 零点保护位置阈值。当伺服反馈位置的绝对值小于此值时需要保护措施。
    /// @return
    int64_t ZeroPositionProtectionThreshold();

    /// @brief 最大转矩的更新频率。
    /// @return
    int UpdateFrequencyOfMaxTorque_Hz();
};
