#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif
#include "src/blacksmith_actions.h"

class RhythmAreaComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 6;
	
	int id;
	float elapsed;
	float totalTime;
	BlacksmithActions action;
	
	RhythmAreaComponent() {}
	
	RhythmAreaComponent(int id, float elapsed, float totalTime, BlacksmithActions action)
		: id(id)
		, elapsed(elapsed)
		, totalTime(totalTime)
		, action(action)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(id, context, node["id"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(elapsed, context, node["elapsed"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(totalTime, context, node["totalTime"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(action, context, node["action"]);
	}
};
