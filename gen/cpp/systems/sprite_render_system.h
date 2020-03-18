#pragma once

#include <halley.hpp>

#include "src/services/painter_service.h"

#include "components/position_component.h"
#include "components/sprite_component.h"
#include "components/sprite_position_override_component.h"
#include "components/text_label_component.h"

// Generated file; do not modify.
template <typename T>
class SpriteRenderSystemBase : private Halley::System {
	friend Halley::System* halleyCreateSpriteRenderSystem();
	
public:
	class SpriteFamily : public Halley::FamilyBaseOf<SpriteFamily> {
	public:
		const PositionComponent& position;
		SpriteComponent& sprite;
		const Halley::MaybeRef<SpritePositionOverrideComponent> spritePositionOverride;
		
		using Type = Halley::FamilyType<PositionComponent, SpriteComponent, Halley::MaybeRef<SpritePositionOverrideComponent>>;
		
	protected:
		SpriteFamily(const PositionComponent& position, SpriteComponent& sprite, const Halley::MaybeRef<SpritePositionOverrideComponent> spritePositionOverride)
			: position(position)
			, sprite(sprite)
			, spritePositionOverride(spritePositionOverride)
		{}
	};
	
	class TextFamily : public Halley::FamilyBaseOf<TextFamily> {
	public:
		const PositionComponent& position;
		TextLabelComponent& textLabel;
		
		using Type = Halley::FamilyType<PositionComponent, TextLabelComponent>;
		
	protected:
		TextFamily(const PositionComponent& position, TextLabelComponent& textLabel)
			: position(position)
			, textLabel(textLabel)
		{}
	};
	
protected:
	
public:
	PainterService* painterService = nullptr;
	PainterService& getPainterService() const {
		return *painterService;
	}
	void initBase() override {
		painterService = &doGetWorld().template getService<PainterService>();
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, SpriteFamily>(spriteFamily, static_cast<T*>(this));
		initialiseFamilyBinding<T, TextFamily>(textFamily, static_cast<T*>(this));
	}
	
protected:
public:
	Halley::FamilyBinding<SpriteFamily> spriteFamily;
protected:
public:
	Halley::FamilyBinding<TextFamily> textFamily;
	
private:
	void renderBase(Halley::RenderContext& rc) override final {
		static_cast<T*>(this)->render(rc);
	}
	
public:
	SpriteRenderSystemBase()
		: System({&spriteFamily, &textFamily}, {})
	{}
};

