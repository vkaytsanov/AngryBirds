#ifndef ANGRY_BIRDS
#define ANGRY_BIRDS

#include "../../lib/include/listener.h"
#include "../scene_editor/include/editor.h"
#include "../screens/include/screen_manager.h"
#include "../data/include/config_development.h"

class AngryBirds : public Listener {
private:
	std::unique_ptr<ScreenManager> m_pScreenManager;
public:
#if defined(USE_EDITOR)
	std::unique_ptr<Editor> m_pEditor;
#endif
	~AngryBirds() override;
public:
	// Inherited via Listener
	void create() override;
	void render() override;
	void renderImGui() override;
	void pause() override;
	void resume() override;
	void resize(const int width, const int height) override;

};

#endif
