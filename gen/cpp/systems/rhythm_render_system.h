#pragma once

#include <halley.hpp>


#include "components/position_component.h"
#include "components/rhythm_area_component.h"
#include "components/camera_component.h"

// Generated file; do not modify.
template <typename T>
class RhythmRenderSystemBase : private Halley::System {
	friend Halley::System* halleyCreateRhythmRenderSystem();
	
public:
	class MainFamily : public Halley::FamilyBaseOf<MainFamily> {
	public:
		const PositionComponent& position;
		const RhythmAreaComponent& rhythmArea;
		
		using Type = Halley::FamilyType<PositionComponent, RhythmAreaComponent>;
		
	protected:
		MainFamily(const PositionComponent& position, const RhythmAreaComponent& rhythmArea)
			: position(position)
			, rhythmArea(rhythmArea)
		{}
	};
	
	class CameraFamily : public Halley::FamilyBaseOf<CameraFamily> {
	public:
		const CameraComponent& camera;
		const PositionComponent& position;
		
		using Type = Halley::FamilyType<CameraComponent, PositionComponent>;
		
	protected:
		CameraFamily(const CameraComponent& camera, const PositionComponent& position)
			: camera(camera)
			, position(position)
		{}
	};
	
protected:
	void initBase() override {
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, MainFamily>(mainFamily, static_cast<T*>(this));
		initialiseFamilyBinding<T, CameraFamily>(cameraFamily, static_cast<T*>(this));
	}
	
public:
	Halley::FamilyBinding<MainFamily> mainFamily;
protected:
public:
	Halley::FamilyBinding<CameraFamily> cameraFamily;
	
private:
	void renderBase(Halley::RenderContext& rc) override final {
		static_cast<T*>(this)->render(rc);
	}
	
public:
	RhythmRenderSystemBase()
		: System({&mainFamily, &cameraFamily}, {})
	{}
};

