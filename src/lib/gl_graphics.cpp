#include <GL/glew.h>
#include <iostream>

#include "include/gl_graphics.h"
#include "include/listener.h"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


GLGraphics::GLGraphics(Configuration* config) : IGraphics(config),
                                                m_pContext(nullptr),
                                                m_pWindow(nullptr),
                                                m_pScreenSurface(nullptr),
                                                m_pRenderer(nullptr){
	
}

GLGraphics::~GLGraphics(){
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	//Destroy openGL m_pContext
	SDL_GL_DeleteContext(m_pContext);
	//Destroy surface
	SDL_FreeSurface(m_pScreenSurface);
	m_pScreenSurface = nullptr;
	//Destroy m_pRenderer
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;
	//Destroy m_pWindow
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	//Shutdown SDL_TTF
	TTF_Quit();
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}

void GLGraphics::initialize() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL INIT ERROR " << SDL_GetError() << "\n";
		exit(-1);
	}
	// Decide OpenGL and GLSL versions
#if defined(__APPLE__)
	// GL 3.2 Core + GLSL 150
	m_glslVersion = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	m_glslVersion = "#version 330 core";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
#endif
	//Create m_pWindow
	m_pWindow = SDL_CreateWindow(m_pConfig->title,
		m_pConfig->x,
		m_pConfig->y,
		m_pConfig->width,
		m_pConfig->height,
		m_pConfig->isVisible | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr) {
		std::cout << SDL_GetError() << "\n";
		exit(-1);
	}

	//Create the m_pContext for OpenGL
	m_pContext = SDL_GL_CreateContext(m_pWindow);


	if (!m_pContext) {
		std::cout << "SDL2 CONTEXT ERROR: " << SDL_GetError() << "\n";
		exit(-1);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_MakeCurrent(m_pWindow, m_pContext);

	// refresh rate synchronized to the monitor
	SDL_GL_SetSwapInterval(1);


	//Get m_pWindow surface
	m_pScreenSurface = SDL_GetWindowSurface(m_pWindow);
	if (m_pScreenSurface == nullptr) {
		std::cout << "SDL2 SCREEN SURFACE ERROR: " << SDL_GetError() << "\n";
		exit(-1);
	}
	//Update the surface
	SDL_UpdateWindowSurface(m_pWindow);
	//Create m_pRenderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	if (m_pRenderer == nullptr) {
		std::cout << "SDL2 RENDERER ERROR: " << SDL_GetError() << "\n";
	}
	
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << glewGetErrorString(err) << "\n";
	}
	int flags = IMG_INIT_PNG;

	//Create Image Handling, but just PNG format
	if (!IMG_Init(flags)) {
		std::cout << "SDL IMG Error: " << IMG_GetError() << "\n";
		exit(-1);
	}

	if (TTF_Init() == -1) {
		std::cout << "SDL2 TTF ERROR: " << TTF_GetError() << "\n";
		exit(-1);
	}

	initImgui();
}

void GLGraphics::initImgui() {

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
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_pContext);
	ImGui_ImplOpenGL3_Init(getGlslVersion());
}


SDL_Window* GLGraphics::getWindow() const {
	return m_pWindow;
}

SDL_Surface* GLGraphics::getScreenSurface() const {
	return m_pScreenSurface;
}

SDL_GLContext GLGraphics::getContext() const {
	return m_pContext;
}

const char* GLGraphics::getGlslVersion() const {
	return m_glslVersion.c_str();
}

void GLGraphics::swapBuffers(Listener* listener){
	// imgui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	listener->renderImGui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(m_pWindow, m_pContext);
	}

	SDL_GL_SwapWindow(m_pWindow);

	/* So we don't use 100% CPU */
	SDL_Delay(1);
	int error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL Error " <<  reinterpret_cast<const char*>(glewGetErrorString(error)) << "\n";
	}
}
