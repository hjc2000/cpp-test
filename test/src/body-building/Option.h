#pragma once

/// @brief 健身模式
enum Option_BodyBuildingMode
{
    Standard
};

class Option
{
private:
    Option_BodyBuildingMode _body_building_mode;
    Option_BodyBuildingMode _last_body_building_mode;

public:
    void Refresh_BodyBuildingMode();
    Option_BodyBuildingMode BodyBuildingMode();
    Option_BodyBuildingMode LastBodyBuildingMode();
    bool BodyBuildingModeChanged();
};
