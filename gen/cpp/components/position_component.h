#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif

class PositionComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 9;
	
	Halley::Vector2f position;
	
	PositionComponent() {}
	
	PositionComponent(Halley::Vector2f position)
		: position(position)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(position, context, node["position"]);
	}
};
