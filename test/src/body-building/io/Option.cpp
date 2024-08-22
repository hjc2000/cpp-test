#include "Option.h"

void Option::Refresh_BodyBuildingMode()
{
    _last_body_building_mode = _body_building_mode;
    // _body_building_mode =
}

Option_BodyBuildingMode Option::BodyBuildingMode()
{
    return _body_building_mode;
}

Option_BodyBuildingMode Option::LastBodyBuildingMode()
{
    return _last_body_building_mode;
}

bool Option::BodyBuildingModeChanged()
{
    return _body_building_mode != _last_body_building_mode;
}

void Option::Refresh_AdditionalMode()
{
    _last_additional_mode = _additional_mode;
    // _additional_mode=
}

Option_AdditionalMode Option::AdditionalMode()
{
    return _additional_mode;
}

Option_AdditionalMode Option::LastAdditionalMode()
{
    return _last_additional_mode;
}

bool Option::AdditionalModeCodeChanged()
{
    return _additional_mode != _last_additional_mode;
}

void Option::Refresh_Tension_kg()
{
    _last_tension_kg = _tension_kg;
    // _tension_kg=
}

double Option::Tension_kg()
{
    return _tension_kg;
}

double Option::LastTension_kg()
{
    return _last_tension_kg;
}

bool Option::Tension_kg_Changed()
{
    return _tension_kg != _last_tension_kg;
}

double Option::MaxTension_kg()
{
    return 0.0;
}

int Option::MinTorque()
{
    return 0;
}

int Option::MaxTorque()
{
    return 0;
}

double Option::WindingSpeed()
{
    return 0.0;
}

double Option::TorqueRatio()
{
    return 1.85;
}

bool Option::UseGravitationPackage()
{
    return false;
}

int Option::ZeroPositionProtectionThreshold()
{
    return 0;
}

int Option::UpdateFrequencyOfMaxTorque_Hz()
{
    return 0;
}

double Option::OverspeedDampingCoefficientThreshold()
{
    return 0.0;
}

double Option::DampingCoefficientWhenOverspeeding()
{
    return 0.0;
}

int Option::IntelligentModeTensionCompensation()
{
    return 0;
}

double Option::WindingSpeedLimitDuringBigWindingResistance()
{
    return 0.0;
}

bool Option::AutoDisableServoAfterReturningToZero()
{
    return false;
}

int Option::ReturnToZeroTorque()
{
    return 0;
}

double Option::ReturnToZeroSpeed()
{
    return 0.0;
}

int Option::ReduceTorque()
{
    return 0;
}

int Option::BigTorque()
{
    return 0;
}
