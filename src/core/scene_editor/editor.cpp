#include "include/editor.h"

#include <fstream>
#include "imgui/imgui.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/memory.hpp>

#include "../components/include/serializable.h"
#include "../components/2d/include/sprite.h"
#include "../components/3d/include/rigid_body.h"
#include "../data/include/entity_factory.h"
#include "../systems/include/transform_system.h"
#include "../systems/include/render_system.h"

Editor::Editor(entityx::EntityX* entityX) : m_pEntityX(entityX),
                                            m_prefabs(m_eventManager) {
	loadPrefabs();
}

void Editor::loadPrefabs() {
	// we dont have the blues(the 3 little blue birds)
	for(int i = Terence; i < JayJakeJim; i++) {
		auto ent = EntityFactory::createEntityFromType(m_prefabs, static_cast<EntityType>(i));
		auto tr = ent.getComponent<Animator>()->getFrame().m_textureRegion;
		ent.getComponent<Sprite>()->m_textureRegion.setRegionUV(tr.getU(), tr.getV(), tr.getU2(), tr.getV2());
		ent.getComponent<Sprite>()->setVao(ent.getComponent<Animator>()->getFrame().getVao());
	}
	{
		auto ent = EntityFactory::createEntityFromType(m_prefabs, PigMinion);
		auto tr = ent.getComponent<Animator>()->getFrame().m_textureRegion;
		ent.getComponent<Sprite>()->m_textureRegion.setRegionUV(tr.getU(), tr.getV(), tr.getU2(), tr.getV2());
		ent.getComponent<Sprite>()->setVao(ent.getComponent<Animator>()->getFrame().getVao());
	}
	for(int i = PigMinion + 1; i < ENTITY_TYPE_SIZE; i++) {
		EntityFactory::createEntityFromType(m_prefabs, static_cast<EntityType>(i));
	}
}

void Editor::onSceneChange() {
	// Create ground
	auto ground = m_pEntityX->entities.create();
	auto ts = ground.addComponent<Transform>(Vector3f(0, -50, 0));
	ts->scale = Vector3f(10, 1.4f, 1);
	TextureRegion groundTR = TextureRegion(AssetManager::getInstance().getSprite("ground"));
	groundTR.setTiling(10, 1);
	ground.addComponent<Sprite>(std::move(groundTR));

	// update the current sprite for the entities with animators, since it is null when loaded
	for(auto ent : m_pEntityX->entities.entities_with_components<Animator>()) {
		auto tr = ent.getComponent<Animator>()->getFrame().m_textureRegion;
		ent.getComponent<Sprite>()->m_textureRegion.setRegionUV(tr.getU(), tr.getV(), tr.getU2(), tr.getV2());
		ent.getComponent<Sprite>()->setVao(ent.getComponent<Animator>()->getFrame().getVao());
	}
}

void Editor::addToCurrentScene(const entityx::Entity entity) {
	auto clone = m_pEntityX->entities.create_from_copy(entity);

	entityx::ComponentHandle<Transform> ch = clone.getComponent<Transform>();

	const Vector2i windowPos = Vector2i(gameWindowTopLeftPos.x, gameWindowTopLeftPos.y);
	const Vector2i windowSize = Vector2i(gameWindowBottomRightPos.x, gameWindowBottomRightPos.y) - windowPos;
	const Vector2i transformed = Viewport::fromScreenToWindowedViewport(windowPos, windowSize, Lib::input->getCurrMousePos());
	ch->position = Vector3f(static_cast<float>(transformed.x), static_cast<float>(-transformed.y), 0);

	isDirty = true;
}

void Editor::update(float dt) {
	// if (isDirty) {
		isDirty = false;
		
		m_fbo.bind();
		m_pEntityX->systems.update<TransformSystem>(0);
		m_pEntityX->systems.postUpdate<RenderSystem>(0);
		m_fbo.unbind();
		
	// }
}



void Editor::renderImGui() {
	static bool show = false;
	//ImGui::ShowDemoWindow(nullptr);
	showDockSpace(&show);


	drawMenuBar();
	drawHierarchy();
	drawSceneWindow();

	drawPrefabsWindow();
	drawAvailableScenesWindow();

	drawDetails();

	drawPopUps();
}

void Editor::showDockSpace(bool* open) {
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen) {
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("###DockSpace", open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else {
		//ShowDockingDisabledMessage();
	}


	ImGui::End();

}

void Editor::drawMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Create New Scene")) {
				m_newScenePopUp = true;
			}
			else if (ImGui::MenuItem("Save Scene")) {
				m_sceneManager.saveCurrentScene(&m_pEntityX->entities);
			}
			// else if (ImGui::MenuItem("Save Scene As")) {
			// 	m_saveAsPopUp = true;
			// }
			ImGui::EndMenu();
		}
		if(m_sceneManager.m_pCurrentScene){
			ImGui::Text(m_sceneManager.m_pCurrentScene->m_fileName.c_str());
		}
		else {
			ImGui::Text("Empty Scene");
		}
		ImGui::EndMainMenuBar();
	}
}

void Editor::drawHierarchy() {
	ImGui::Begin("Hierarchy");
	{
		for (auto entity : m_pEntityX->entities.entities_with_components<Transform>()) {
			std::string label = "Entity " + std::to_string(entity.id().index());
			const bool isSelected = m_pSelectedEntity.id().index() == entity.id().index();

			if (ImGui::Selectable(label.c_str(), isSelected)) {
				m_pSelectedEntity = entity;
				assert(m_pSelectedEntity.valid());
			}
		}
	}
	ImGui::End();
}


void Editor::drawSceneWindow() {
	ImGui::Begin("Scene Window");

	gameWindowTopLeftPos = ImGui::GetWindowContentRegionMin();
	gameWindowBottomRightPos = ImGui::GetWindowContentRegionMax();

	gameWindowTopLeftPos.x += ImGui::GetWindowPos().x;
	gameWindowTopLeftPos.y += ImGui::GetWindowPos().y;
	gameWindowBottomRightPos.x += ImGui::GetWindowPos().x;
	gameWindowBottomRightPos.y += ImGui::GetWindowPos().y;
	ImGui::GetWindowDrawList()->AddImage((void*)m_fbo.getTextureBuffer(), gameWindowTopLeftPos,
	                                     gameWindowBottomRightPos,
	                                     ImVec2(0, 1), ImVec2(1, 0));

	// Dropping prefabs to scene area
	ImVec2 gameWindowArea;
	gameWindowArea.x = gameWindowBottomRightPos.x - gameWindowTopLeftPos.x;
	gameWindowArea.y = gameWindowBottomRightPos.y - gameWindowTopLeftPos.y;

	// so we can drop in the window, https://github.com/ocornut/imgui/issues/1771
	ImGui::InvisibleButton("Prefab Payload", gameWindowArea);
	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Prefab")) {
			if(payload->DataSize != sizeof(entityx::Entity)) return;
			auto entity = *(const entityx::Entity*)payload->Data;
			if(!entity.valid()) return;
			addToCurrentScene(entity);
		}
		ImGui::EndDragDropTarget();
	}
	ImGui::End();
}

void Editor::drawDetails() {
	ImGui::Begin("Details");
	{
		if (m_pSelectedEntity.valid()) {
			ImGui::BeginChild("Components");

			drawTransformComponentWidget();

			ImGui::EndChild();
		}
	}
	ImGui::End();
}

void Editor::drawPrefabsWindow() {
	ImGui::Begin("Prefabs");
	{
		for (auto entity : m_prefabs.entities_with_components<Sprite>()) {
			ImGui::PushID(entity.id().index());
			ImGui::SameLine();
			ImGui::BeginGroup();
			TextureRegion* tR = &entity.getComponent<Sprite>()->m_textureRegion;

			ImGui::ImageButton(
				(void*)tR->getTexture()->getBuffer(), {64, 64}, {tR->getU(), tR->getV()}, {tR->getU2(), tR->getV2()});

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
				ImGui::SetDragDropPayload("Prefab", &entity, sizeof(entity));
				ImGui::Text("Add to Scene");
				ImGui::EndDragDropSource();
			}
			ImGui::EndGroup();
			ImGui::PopID();
		}
	}
	ImGui::End();
}

void Editor::drawAvailableScenesWindow() {
	const std::shared_ptr<Texture> icon = m_editorAssetManager.getIcon("bin");

	ImGui::Begin("Scenes");
	for (auto& it : m_sceneManager.m_scenes) {
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::ImageButton((void*)icon->getBuffer(), {64, 64}, {0, 0}, {1, 1});
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
			m_sceneManager.changeScene(&m_pEntityX->entities, it.first);
			onSceneChange();
			isDirty = true;
		}
		ImGui::Text("%s", it.first.c_str());
		ImGui::EndGroup();
	}
	ImGui::End();
}

void Editor::drawTransformComponentWidget() {
	static bool close = true;
	if (ImGui::CollapsingHeader("Transform", &close, ImGuiTreeNodeFlags_DefaultOpen)) {
		entityx::ComponentHandle<Transform> ch = m_pSelectedEntity.getComponent<Transform>();
		if (ImGui::TreeNodeEx("Position", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushItemWidth(50);
			if (ImGui::InputFloat("X", &ch->position.x)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			if (ImGui::InputFloat("Y", &ch->position.y)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			if (ImGui::InputFloat("Z", &ch->position.z)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::NewLine();
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Rotation", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushItemWidth(50);
			if (ImGui::InputFloat("X", &ch->eulerAngles.x)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			if (ImGui::InputFloat("Y", &ch->eulerAngles.y)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			if (ImGui::InputFloat("Z", &ch->eulerAngles.z)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::NewLine();
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Scale", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushItemWidth(50);
			if (ImGui::InputFloat("X", &ch->scale.x)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			if (ImGui::InputFloat("Y", &ch->scale.y)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			if (ImGui::InputFloat("Z", &ch->scale.z)) {
				ch->hasChanged = true;
				isDirty = true;
			}
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::TreePop();
		}
	}
}

void Editor::drawPopUps() {
	if (m_saveAsPopUp) {
		ImGui::OpenPopup("Save Scene As");
	}
	ImGui::SetNextWindowSizeConstraints(ImVec2(200, 110), ImVec2(200, 110));
	if (ImGui::BeginPopupModal("Save Scene As")) {
		static char name[64] = "";
		ImGui::Text("Name");
		ImGui::SetNextItemWidth(180);
	
		ImGui::InputText("##name", name, sizeof(name));
		
		if (ImGui::Button("Save", {85, 30})) {
			m_sceneManager.createScene(&m_pEntityX->entities, name);
			ImGui::CloseCurrentPopup();
			m_saveAsPopUp = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel", {85, 30})) {
			ImGui::CloseCurrentPopup();
			m_saveAsPopUp = false;
		}
		ImGui::EndPopup();
	}

	if (m_newScenePopUp) {
		ImGui::OpenPopup("Create New Scene");
	}
	ImGui::SetNextWindowSizeConstraints(ImVec2(200, 110), ImVec2(200, 110));
	if (ImGui::BeginPopupModal("Create New Scene")) {
		static char name[64] = "";
		ImGui::Text("Name");
		ImGui::SetNextItemWidth(180);
	
		ImGui::InputText("##name", name, sizeof(name));
		
		if (ImGui::Button("Create", {85, 30})) {
			m_sceneManager.createScene(&m_pEntityX->entities, name);
			ImGui::CloseCurrentPopup();
			m_newScenePopUp = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel", {85, 30})) {
			ImGui::CloseCurrentPopup();
			m_newScenePopUp = false;
		}
		ImGui::EndPopup();
	}
}
