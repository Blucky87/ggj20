#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif

class EnvironmentObjectComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 11;
	
	Halley::String id;
	float animTime;
	Halley::String animTarget;
	
	EnvironmentObjectComponent() {}
	
	EnvironmentObjectComponent(Halley::String id, float animTime, Halley::String animTarget)
		: id(id)
		, animTime(animTime)
		, animTarget(animTarget)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(id, context, node["id"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(animTime, context, node["animTime"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(animTarget, context, node["animTarget"]);
	}
};
