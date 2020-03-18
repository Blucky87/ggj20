#include <halley.hpp>
using namespace Halley;

#include "halley/entity/components/transform_2d_component.h"
#include "components/text_label_component.h"
#include "components/sprite_component.h"
#include "components/sprite_animation_component.h"
#include "components/item_component.h"
#include "components/camera_component.h"
#include "components/particle_component.h"
#include "components/rhythm_area_component.h"
#include "components/move_animation_component.h"
#include "components/position_component.h"
#include "components/sprite_position_override_component.h"
#include "components/environment_object_component.h"
#include "components/bouncy_component.h"
#include "components/ui_component.h"

// System factory functions
System* halleyCreateCameraRenderSystem();
System* halleyCreateCameraSystem();
System* halleyCreateItemsSystem();
System* halleyCreateParticleSystem();
System* halleyCreateRhythmRenderSystem();
System* halleyCreateEnvironmentObjectSystem();
System* halleyCreateRhythmSystem();
System* halleyCreateMoveSystem();
System* halleyCreateGameStateSystem();
System* halleyCreateSpriteRenderSystem();
System* halleyCreateSpriteAnimationSystem();
System* halleyCreateUISystem();
System* halleyCreateUIRenderSystem();


using SystemFactoryPtr = System* (*)();
using SystemFactoryMap = HashMap<String, SystemFactoryPtr>;

static SystemFactoryMap makeSystemFactories() {
	SystemFactoryMap result;
	result["CameraRenderSystem"] = &halleyCreateCameraRenderSystem;
	result["CameraSystem"] = &halleyCreateCameraSystem;
	result["ItemsSystem"] = &halleyCreateItemsSystem;
	result["ParticleSystem"] = &halleyCreateParticleSystem;
	result["RhythmRenderSystem"] = &halleyCreateRhythmRenderSystem;
	result["EnvironmentObjectSystem"] = &halleyCreateEnvironmentObjectSystem;
	result["RhythmSystem"] = &halleyCreateRhythmSystem;
	result["MoveSystem"] = &halleyCreateMoveSystem;
	result["GameStateSystem"] = &halleyCreateGameStateSystem;
	result["SpriteRenderSystem"] = &halleyCreateSpriteRenderSystem;
	result["SpriteAnimationSystem"] = &halleyCreateSpriteAnimationSystem;
	result["UISystem"] = &halleyCreateUISystem;
	result["UIRenderSystem"] = &halleyCreateUIRenderSystem;
	return result;
}


using ComponentFactoryPtr = std::function<void(EntityFactory&, EntityRef&, const ConfigNode&)>;
using ComponentFactoryMap = HashMap<String, ComponentFactoryPtr>;

static ComponentFactoryMap makeComponentFactories() {
	ComponentFactoryMap result;
	result["Transform2D"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<Transform2DComponent>(e, node); };
	result["TextLabel"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<TextLabelComponent>(e, node); };
	result["Sprite"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<SpriteComponent>(e, node); };
	result["SpriteAnimation"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<SpriteAnimationComponent>(e, node); };
	result["Item"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<ItemComponent>(e, node); };
	result["Camera"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<CameraComponent>(e, node); };
	result["Particle"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<ParticleComponent>(e, node); };
	result["RhythmArea"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<RhythmAreaComponent>(e, node); };
	result["MoveAnimation"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<MoveAnimationComponent>(e, node); };
	result["Position"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<PositionComponent>(e, node); };
	result["SpritePositionOverride"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<SpritePositionOverrideComponent>(e, node); };
	result["EnvironmentObject"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<EnvironmentObjectComponent>(e, node); };
	result["Bouncy"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<BouncyComponent>(e, node); };
	result["UI"] = [] (EntityFactory& factory, EntityRef& e, const ConfigNode& node) { factory.createComponent<UIComponent>(e, node); };
	return result;
}

namespace Halley {
	std::unique_ptr<System> createSystem(String name) {
		static SystemFactoryMap factories = makeSystemFactories();
		auto result = factories.find(name);
		if (result == factories.end()) {
			throw Exception("System not found: " + name, HalleyExceptions::Entity);
		}
		return std::unique_ptr<System>(result->second());
	}

   void createComponent(EntityFactory& factory, const String& name, EntityRef& entity, const ConfigNode& componentData) {
		static ComponentFactoryMap factories = makeComponentFactories();
		auto result = factories.find(name);
		if (result == factories.end()) {
			throw Exception("Component not found: " + name, HalleyExceptions::Entity);
		}
		return result->second(factory, entity, componentData);
   }
}
