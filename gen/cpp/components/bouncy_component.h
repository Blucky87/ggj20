#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif

class BouncyComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 12;
	
	float bounceTime;
	float bounceAmplitude;
	
	BouncyComponent() {}
	
	BouncyComponent(float bounceTime, float bounceAmplitude)
		: bounceTime(bounceTime)
		, bounceAmplitude(bounceAmplitude)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(bounceTime, context, node["bounceTime"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(bounceAmplitude, context, node["bounceAmplitude"]);
	}
};
