#include "include/editor.h"

#include "imgui/imgui.h"

void Editor::update(float dt) {
}

void Editor::renderImGui(entityx::EntityManager& entities) {
	bool show = false;
	ImGui::ShowDemoWindow(nullptr);
	showDockSpace(&show);

	ImGui::Begin("Hierarchy");
	{
		ImGui::BeginChild("entities");
		for (auto entity : entities.entities_with_components<Transform>()) {
			std::string label = "Entity " + std::to_string(entity.id().index());
			const bool highlight = m_selectedEntity && m_selectedEntity->id().index() == entity.id().index();

			if (ImGui::Selectable(label.c_str(), highlight)) {
				m_selectedEntity = &entity;
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();

	ImGui::Begin("Scene Window");
	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();

	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;
	ImGui::GetWindowDrawList()->AddImage((void*)m_fbo.getTextureBuffer(), vMin, vMax,
	                                     ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();

	ImGui::Begin("Details");
	{
		if (m_selectedEntity) {
			ImGui::BeginChild("Components");

			drawTransformComponentWidget();

			ImGui::EndChild();
		}
	}
	ImGui::End();

	ImGui::Begin("Prefabs");
	ImGui::End();

	ImGui::Begin("Scenes");
	ImGui::End();
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

void Editor::drawTransformComponentWidget() {
	static bool close = true;
	if (ImGui::CollapsingHeader("Transform", &close, ImGuiTreeNodeFlags_DefaultOpen)) {
		entityx::ComponentHandle<Transform> ch = m_selectedEntity->getComponent<Transform>();
		if (ImGui::TreeNodeEx("Position", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushItemWidth(50);
			if(ImGui::InputFloat("X", &ch->position.x)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			if(ImGui::InputFloat("Y", &ch->position.y)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			if(ImGui::InputFloat("Z", &ch->position.z)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::NewLine();
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Rotation", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushItemWidth(50);
			if(ImGui::InputFloat("X", &ch->eulerAngles.x)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			if(ImGui::InputFloat("Y", &ch->eulerAngles.y)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			if(ImGui::InputFloat("Z", &ch->eulerAngles.z)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::NewLine();
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Scale", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushItemWidth(50);
			if(ImGui::InputFloat("X", &ch->scale.x)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			if(ImGui::InputFloat("Y", &ch->scale.y)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			if(ImGui::InputFloat("Z", &ch->scale.z)) {
				ch->hasChanged = true;
			}
			ImGui::SameLine();
			ImGui::PopItemWidth();
			ImGui::TreePop();
		}
	}
}
