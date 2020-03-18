#pragma once

#include <halley.hpp>

#include "src/move_type.h"

class MoveMessage final : public Halley::Message {
public:
	static constexpr int messageIndex = 0;
	
	Halley::Vector2f to;
	float len;
	MoveType moveType;
	
	MoveMessage() {}
	
	MoveMessage(Halley::Vector2f to, float len, MoveType moveType)
		: to(to)
		, len(len)
		, moveType(moveType)
	{}
	
	size_t getSize() const override final {
		return sizeof(MoveMessage);
	}
};
