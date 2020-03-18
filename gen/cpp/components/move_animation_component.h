#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif
#include "src/move_type.h"

class MoveAnimationComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 8;
	
	bool moving;
	Halley::Vector2f start;
	Halley::Vector2f end;
	float len;
	float curTime;
	MoveType moveType;
	
	MoveAnimationComponent() {}
	
	MoveAnimationComponent(bool moving, Halley::Vector2f start, Halley::Vector2f end, float len, float curTime, MoveType moveType)
		: moving(moving)
		, start(start)
		, end(end)
		, len(len)
		, curTime(curTime)
		, moveType(moveType)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(moving, context, node["moving"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(start, context, node["start"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(end, context, node["end"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(len, context, node["len"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(curTime, context, node["curTime"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(moveType, context, node["moveType"]);
	}
};
