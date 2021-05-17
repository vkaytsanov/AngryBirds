#include "include/editor.h"

#include <fstream>

#include "../lib/imgui/imgui.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/memory.hpp>

#include "../components/include/serializable.h"
#include "../components/2d/include/sprite.h"
#include "../components/3d/include/rigid_body.h"


Editor::Editor(entityx::EntityX* entityX) : m_pEntityX(entityX),
                                            m_prefabs(m_eventManager) {
	loadPrefabs();
}

void Editor::loadPrefabs() {
	std::ifstream is("prefabs.bin");
	cereal::BinaryInputArchive archive(is);


	std::vector<SerializableComponent<Transform>> transforms;
	std::vector<SerializableComponent<RigidBody>> rigidBodys;
	std::vector<SerializableComponent<Sprite>> spriteDeserializes;

	archive(transforms);
	archive(rigidBodys);
	archive(spriteDeserializes);

	for (unsigned i = 0; i < transforms.size(); i++) {
		std::cout << "TransformX: " << transforms[i].component.position.x << "\n";
		auto entity = m_prefabs.create();
		entity.addComponent<Transform>(transforms[i].component);
	}

	for (unsigned i = 0; i < rigidBodys.size(); i++) {
		std::cout << "RigidBodyUseG: " << rigidBodys[i].component.m_useGravity << "\n";
		m_prefabs.addComponent<RigidBody>(entityx::Entity::Id(rigidBodys[i].id), rigidBodys[i].component);
	}

	for (unsigned i = 0; i < spriteDeserializes.size(); i++) {
		std::cout << "TextName: " << spriteDeserializes[i].component.m_textureRegion.getTexture()->m_name << "\n";
		m_prefabs.addComponent<Sprite>(entityx::Entity::Id(spriteDeserializes[i].id),
		                               std::move(spriteDeserializes[i].component));
	}
}

void Editor::addToCurrentScene(const entityx::Entity entity) {
	auto clone = m_pEntityX->entities.create_from_copy(entity);

	entityx::ComponentHandle<Transform> ch = clone.getComponent<Transform>();
	ImVec2 pos = ImGui::GetMousePos();
	ImVec2 dropPos;

	const ImVec2 gameWindowCenter((gameWindowBottomRightPos.x + gameWindowTopLeftPos.x) / 2,
	                              (gameWindowBottomRightPos.y + gameWindowTopLeftPos.y) / 2);
	dropPos.x = pos.x - gameWindowCenter.x;
	dropPos.y = gameWindowCenter.y - pos.y;
	ch->position = Vector3f(dropPos.x, dropPos.y, 0);

	isDirty = true;
}

void Editor::update(float dt) {
	if (isDirty) {
		m_fbo.bind();
		m_pEntityX->systems.updateAll(0);
		m_fbo.unbind();
		isDirty = false;
	}
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
			else if (ImGui::MenuItem("Save Scene As")) {
				m_saveAsPopUp = true;
			}
			ImGui::EndMenu();
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
			IM_ASSERT(payload->DataSize == sizeof(entityx::Entity));

			addToCurrentScene(*(const entityx::Entity*)payload->Data);
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
			const TextureRegion* tR = &entity.getComponent<Sprite>()->m_textureRegion;

			ImGui::ImageButton(
				(void*)tR->getTexture()->getBuffer(), {64, 64}, {tR->getU(), tR->getU2()}, {tR->getV(), tR->getV2()});

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
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
