#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif

class UIComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 13;
	
	Halley::String id;
	
	UIComponent() {}
	
	UIComponent(Halley::String id)
		: id(id)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(id, context, node["id"]);
	}
};
