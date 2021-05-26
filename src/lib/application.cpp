//
// Created by Viktor on 17.12.2020 г..
//


#include "include/application.h"
#include "include/lib.h"
#include <string>

#include <typeinfo>

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <SDL2/SDL.h>
#else
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#endif


#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// TODO Refactor this in other application class
#if defined(__EMSCRIPTEN__)
void emscriptenLoop(void* arg) {
	Application* app = static_cast<Application*>(arg);
	// fetching all the user input
	app->input->update();
	// processing the input by giving it to the processors
	app->input->processEvents();

	app->graphics->updateTime();
	app->listener->render();

	emscripten_sleep(10);

}
#endif

Application::Application(Listener* listener) :
	Application(listener, new Configuration()) {
}

Application::Application(Listener* listener, Configuration* config) :
	Application(listener, config, new Graphics(config)) {
}

/* Initializing here the application */
Application::Application(Listener* listener, Configuration* config, Graphics* graphics) {

	// Our m_pGame
	this->listener = listener;
	// Our configuration file for the m_pGame
	this->config = config;
	// Our library for graphics
	this->graphics = graphics;
	// Logging, debugging and errors utility
	this->logger = new Logger();
	// Receive user input
	this->input = new Input(config->width, config->height);
	// Our library for audio
	this->audio = new Audio();
	// if we dont have declared title, we will use the name of the class
	if (config->title == nullptr) config->title = typeid(listener).name();
	// creating the m_pWindow
	graphics->createWindow();
	// creating the environment lib
	Lib::app = this;
	Lib::graphics = graphics;
	Lib::input = input;
	Lib::audio = audio;
	// creating the objects from the m_pGame
	listener->create();

	initImgui();

	// reset the delta time so we dont get huge value after long initialization of the game
	graphics->m_lastTime = SDL_GetTicks();

	running = true;

#if defined(__EMSCRIPTEN__)
	emscripten_set_main_loop_arg(&emscriptenLoop, this, -1, 1);
#else
	gameLoop();
#endif
}


void Application::gameLoop() {
	int lastWidth = graphics->getWidth();
	int lastHeight = graphics->getHeight();
	bool wasPaused = false;

	while (running) {
		// fetching all the user input
		input->update();
		// processing the input by giving it to the processors
		input->processEvents();
		// user has clicked the front right "X" m_quit button
		if (input->shouldQuit()) break;
		bool isMinimized = !graphics->isVisible();
		bool isBackground = graphics->isBackground();
		bool isPaused = isMinimized || isBackground;
		if (!wasPaused && isPaused) {
			// the m_pGame m_pWindow just became not active on the user's end
			wasPaused = true;
			listener->pause();
		}
		if (wasPaused && !isPaused) {
			// the m_pGame m_pWindow just became active on the user's end
			wasPaused = false;
			listener->resume();
		}

		const int width = graphics->getWidth();
		const int height = graphics->getHeight();
		if (lastWidth != width || lastHeight != height) {
			// we should have received any changes in the input->update()
			lastWidth = width;
			lastHeight = height;
			// sending to the listener that the user has resized
			// it should update the m_pViewport if there is one
			listener->resize(width, height);
		}

		if (!isPaused) {
			graphics->updateTime();
			listener->render();
#if !defined(__EMSCRIPTEN__)
			// imgui
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(graphics->getWindow());
			ImGui::NewFrame();

			listener->renderImGui();

			ImGui::Render();
			//glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			//
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(graphics->getWindow(), graphics->getContext());
			}
#endif
			SDL_GL_SwapWindow(graphics->getWindow());

			/* So we don't use 100% CPU */
			SDL_Delay(1);
		}
		else {
			SDL_Delay(1000);
		}
#if !defined(__EMSCRIPTEN__)
		int error;
		while ((error = glGetError()) != GL_NO_ERROR) {
			this->error("OpenGL Error", reinterpret_cast<const char*>(glewGetErrorString(error)));
		}
#endif
	}
}


void Application::initImgui() {
#if !defined(__EMSCRIPTEN__)
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	// //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows


	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
	colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
	colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ImGuiCol_DockingPreview] = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

	style->ChildRounding = 4.0f;
	style->FrameBorderSize = 1.0f;
	style->FrameRounding = 2.0f;
	style->GrabMinSize = 7.0f;
	style->PopupRounding = 2.0f;
	style->ScrollbarRounding = 12.0f;
	style->ScrollbarSize = 13.0f;
	style->TabBorderSize = 1.0f;
	style->TabRounding = 0.0f;
	style->WindowRounding = 4.0f;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(graphics->getWindow(), graphics->getContext());
	ImGui_ImplOpenGL3_Init(graphics->getGlslVersion());
#endif
}

void Application::exitApp() {
	running = false;
}

Application::~Application() {
#if !defined(__EMSCRIPTEN__)
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
#endif
	delete listener;
	delete audio;
	delete logger;
	delete graphics;
	delete config;

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}

void Application::log(const char* tag, const char* message) const {
	logger->log(tag, message);
}

void Application::error(const char* tag, const char* message) const {
	logger->error(tag, message);
}

void Application::error(const char* tag, int message) const {
	logger->error(tag, std::to_string(message).c_str());
}

void Application::log(const char* tag, int message) const {
	logger->log(tag, std::to_string(message).c_str());
}

void Application::debug(const char* tag, const char* message) const {
	logger->debug(tag, message);
}
