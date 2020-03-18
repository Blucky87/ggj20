#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif

class SpritePositionOverrideComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 10;
	
	Halley::Maybe<Halley::Vector2f> position;
	
	SpritePositionOverrideComponent() {}
	
	SpritePositionOverrideComponent(Halley::Maybe<Halley::Vector2f> position)
		: position(position)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(position, context, node["position"]);
	}
};
