#pragma once

#ifndef DONT_INCLUDE_HALLEY_HPP
#include <halley.hpp>
#endif
#include "src/item_state.h"

class ItemComponent final : public Halley::Component {
public:
	static constexpr int componentIndex = 7;
	
	int id;
	Halley::String type;
	ItemState state;
	
	ItemComponent() {}
	
	ItemComponent(int id, Halley::String type, ItemState state)
		: id(id)
		, type(type)
		, state(state)
	{}
	
	void deserialize(Halley::ConfigNodeSerializationContext& context, const Halley::ConfigNode& node) {
		Halley::ConfigNodeHelper::deserializeIfDefined(id, context, node["id"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(type, context, node["type"]);
		Halley::ConfigNodeHelper::deserializeIfDefined(state, context, node["state"]);
	}
};
