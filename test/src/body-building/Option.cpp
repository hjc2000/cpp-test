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
