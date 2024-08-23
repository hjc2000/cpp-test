#include "AssistanceMode.h"
#include <base/math/InertialElement.h>
#include <ChXFilter.h>
#include <Cmd.h>
#include <DirectionDetector.h>
#include <lua_api.h>
#include <memory>
#include <Option.h>
#include <PullLengthDetecter.h>
#include <PullTimesDetector.h>
#include <Servo.h>
#include <TensionLinearInterpolator.h>

void AssistanceMode::OnFromUnwindingToWinding()
{
    // 	zlPullCnt = zlPullCnt + 1
    // 	--print("助力次数：", zlPullCnt,"--------------------------------")
    // 	if (zlPullCnt < 2) then
    // 		zlSub = 0
    // 		zlTrigger = 0
    // 		torqueZl = Option_Current_Tension_kg()
    // 		torqueZlOut = torqueZl
    // 	elseif (zlPullCnt == 2) then
    // 		zlDist1 = pull_distance
    // 		zlTim1 = _burn_out_ticks
    // 		print("拉出长度：", pull_distance, "拉出时间:", _burn_out_ticks)
    // 	elseif (zlPullCnt == 3) then
    // 		zlDist2 = pull_distance
    // 		zlTim2 = _burn_out_ticks
    // 		zlDistBase = (zlDist1 + zlDist2) / 2 * 0.9
    // 		zlTimBase = (zlTim1 + zlTim2) / 2 + 500
    // 		print("拉出长度：", pull_distance, "拉出时间:", _burn_out_ticks)
    // 		print("长度基准：", zlDistBase, "时间基准", zlTimBase)
    // 	end
    // end

    // zlTrigger = 0
    // needChk = 0
    // if (zlTriggerLst == 1) then
    // 	print("开始回绳助力停止")
    // end
}

void AssistanceMode::OnFromWindingToUnwinding()
{
    // _origin_distance = DirectionDetector_ReleasedLengthOfLineOnDirectionChange()

    // if (_has_effective_winding) then
    // 	-- 经历了有效的收线
    // 	_has_effective_winding = false

    // 	zlPullCnt2 = zlPullCnt2 + 1
    // 	print("助力次数：", zlPullCnt2, "--------------------------------")
    // 	needChk = 1

    // 	--零点位置停止助力
    // 	if (Servo_FeedbackPosition() < zeroPos) then
    // 		if (needChk == 1 and (not State_IsForward())) then
    // 			needChk = 0
    // 			print("进入零点位置，无需助力")
    // 		end
    // 	end

    // 	if (zlPullCnt2 > 3) then
    // 		-- 力气达到最小值则停止助力
    // 		if (torqueZl <= 1) then
    // 			needChk = 0
    // 			torqueZl = 1
    // 			zlTrigger = 0
    // 			if (zlTriggerLst == 1) then
    // 				print("已经到达最低阻力，助力停止")
    // 				zlTriggerLst = 0
    // 			end
    // 		end

    // 		--时间距离判断
    // 		zLDist = State_CurrentReleasedLengthOfLine() - _origin_distance
    // 		if (zlTimCnt > zlTimBase) then
    // 			if (zLDist < zlDistBase and needChk == 1) then
    // 				zlTrigger = 1
    // 				if (zlTriggerLst == 0) then
    // 					print("当前长度：", zLDist, "当前时间：", zlTimCnt)
    // 					print("触发助力")
    // 					zlTriggerLst = 1
    // 				end
    // 			else
    // 				needChk = 0
    // 				zlTrigger = 0
    // 				if (zlTriggerLst == 1) then
    // 					print("长度达标，助力停止")
    // 					zlTriggerLst = 0
    // 				end
    // 			end
    // 		end

    // 		zlTriggerLst = zlTrigger
    // 	end

    // 	if (zlTrigger == 1) then
    // 		zlSubCnt = zlSubCnt + 1
    // 	else
    // 		zlSubCnt = 0
    // 	end

    // 	if (zlSubCnt == 1) then
    // 		--首次助力
    // 		if (zlSub == 1) then --上次助力未完成，直接切换至最新力气
    // 			--计算减力基准值
    // 			zlTrqBase = zlTrqBase - zlSubTrq
    // 		else
    // 			zlSub = 1
    // 			--计算减力基准值
    // 			zlTrqBase = torqueZl
    // 		end
    // 		zlSubTrqCnt = 0
    // 		print("首次助力，当前公斤数：", (zlTrqBase * 5 + 15) / 10)
    // 		zlSubTrq = CalSubKg(torqueZl)
    // 		torqueZlOut = zlTrqBase - zlSubTrq
    // 		print("zlSubTrq:", zlSubTrq)
    // 	end

    // 	if (zlSub == 1) then
    // 		zlSubTrqCnt = zlSubTrqCnt + 1
    // 		torqueZl = zlTrqBase - zlSubTrq * (zlSubTrqCnt / 1500)
    // 		if (zlSubTrqCnt >= 1500) then
    // 			zlSub = 0
    // 			zlSubTrqCnt = 0
    // 			if (zlTrigger == 1) then
    // 				zlSub = 1
    // 				zlTrqBase = torqueZl
    // 				print("二次助力，当前公斤数：", (zlTrqBase * 5 + 15) / 10)
    // 				zlSubTrq = CalSubKg(torqueZl)
    // 				torqueZlOut = zlTrqBase - zlSubTrq
    // 				--print("zlSubTrq:",zlSubTrq)
    // 			end
    // 		end
    // 	end

    // 	if (torqueZlOut < 1) then
    // 		torqueZlOut = 1
    // 	end

    // 	Tension_kg_LinearInterpolator_ChangeTensionEndValue(torqueZl)
    // end
}

double AssistanceMode::CalSubKg(double base_kg)
{
    double zlSubkg = (base_kg * 5 + 15) * 0.2;
    double zlSubkgV = static_cast<int>(zlSubkg / 5) * 5;
    if (zlSubkg - zlSubkgV > 0)
    {
        zlSubkgV = zlSubkgV + 5;
    }

    return zlSubkgV * 0.2;
}

void AssistanceMode::Execute()
{
    Cmd::Instance().SetSpeed(Option::Instance().WindingSpeed());

    if (Option::Instance().BodyBuildingModeChanged() || Option::Instance().Tension_kg_Changed())
    {
        TensionLinearInterpolator::Instance().ChangeEndValue(Option::Instance().Tension_kg());
        PullTimesDetector::Instance().Reset();
    }

    if (Servo::Instance().FeedbackSpeed() > 10)
    {
        _unwinding_tick++;
    }

    if (PullTimesDetector::Instance().UnwindingTimesChanged())
    {
        // 经历了有效放线
        _has_effective_unwinding = true;
    }
    else if (PullTimesDetector::Instance().WindingTimesChanged())
    {
        // 经历了有效收线
        _has_effective_winding = true;
    }

    if (DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromUnwindingToWinding)
    {
        // 从放线变成收线
        if (_has_effective_unwinding)
        {
            _has_effective_unwinding = false;
            OnFromUnwindingToWinding();
        }
    }
    else if (DirectionDetector::Instance().DirectionChange() == DirectionDetector_DirectionChange::FromWindingToUnwinding)
    {
        // 从收线变成放线
        if (_has_effective_winding)
        {
            _has_effective_winding = false;
            OnFromWindingToUnwinding();
        }
    }

    DD(14, _tension * 5 + 15);
    double tension = TensionLinearInterpolator::Instance().StepForward();
    double torque = tension * Option::Instance().TorqueRatio();
    Cmd::Instance().SetTorque(torque);
}
