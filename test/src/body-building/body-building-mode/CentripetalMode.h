#pragma once
#include <base/math/InertialElement.h>
#include <lua_api.h>
#include <memory>

/// @brief 向心模式
class CentripetalMode
{
private:
    CentripetalMode() = default;

    /// @brief 大于 1 的值。
    /// @note 向心模式下，顺从它向心，拉力会减小。减小拉力是通过将转矩除以本系数。
    /// @return
    double Ratio()
    {
        return SRV_PARA(1, 43);
    }

    std::shared_ptr<base::InertialElement> _filter{
        new base::InertialElement{
            base::InertialElement_TimeConstant{0.025},
            base::InertialElement_SampleInterval{0.002},
        },
    };

public:
    static CentripetalMode &Instance()
    {
        static CentripetalMode o;
        return o;
    }

    void Execute();
};
