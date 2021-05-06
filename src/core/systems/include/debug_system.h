//
// Created by Viktor on 11.3.2021 г..
//

#ifndef DEBUG_SYSTEM_H
#define DEBUG_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../components/include/transform.h"
#include "../../../lib/utils/ui/include/user_interface.h"
#include "../../../lib/utils/ui/include/label.h"
#include "../../../lib/utils/include/shaders.h"

class DebugSystem : public entityx::System<DebugSystem>{
private:
	UserInterface m_userInterface;
	TTF_Font* m_pFont;
	Label m_playerPos;
	Label m_playerForward;
	LabelStyle* m_pLabelStyle;

	Transform* m_transform;
	bool m_isWireframe = false;
public:
	DebugSystem();
	~DebugSystem() override;
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //DEBUG_SYSTEM_H
