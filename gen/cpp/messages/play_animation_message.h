#pragma once

#include <halley.hpp>


class PlayAnimationMessage final : public Halley::Message {
public:
	static constexpr int messageIndex = 1;
	
	Halley::String sequence;
	
	PlayAnimationMessage() {}
	
	PlayAnimationMessage(Halley::String sequence)
		: sequence(sequence)
	{}
	
	size_t getSize() const override final {
		return sizeof(PlayAnimationMessage);
	}
};
