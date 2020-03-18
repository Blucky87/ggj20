#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif

class ParticleComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 5;
	
	Halley::Vector2f vel;
	
	ParticleComponent() {}
	
	ParticleComponent(Halley::Vector2f vel)
		: vel(vel)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(vel, context, node["vel"]);
	}
};
