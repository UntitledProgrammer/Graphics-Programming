#include "DisplayWindow.h"

DisplayWindow::DisplayWindow(SDL_Window* window) : window(window)
{
	//Setup imGui.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	//ImGuiSDL::Initialize(Renderer::Get(), displayMode.w, displayMode.h);
	ImGuiIO& ios = ImGui::GetIO();
	(void)ios;
	ios.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ios.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ios.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ios.ConfigFlags |= ImGuiInputTextFlags_CallbackEdit;
	ImGui::StyleColorsDark();
	context = SDL_GL_CreateContext(window);
	ImGui_ImplSDL2_InitForOpenGL(window, &context);
}

/*
DisplayWindow::DisplayWindow(Polygon* poly) : polygon(poly)
{
	//Setup imGui.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	ImGuiSDL::Initialize(Renderer::Get(), displayMode.w, displayMode.h);
	ImGuiIO& ios = ImGui::GetIO();
	(void)ios;
	ios.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ios.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ios.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ios.ConfigFlags |= ImGuiInputTextFlags_CallbackEdit;
	ImGui::StyleColorsDark();
	context = SDL_GL_CreateContext(polygon->window);
	ImGui_ImplSDL2_InitForOpenGL(polygon->window, &context);
	gameObject = polygon->sceneManager->activeScene->createGameObject();
	gameObject->addComponent<Sprite>();
	gameObject->addComponent<RigidBody>();
}
*/
DisplayWindow::~DisplayWindow()
{

}

void DisplayWindow::Update()
{
	bool active = false;
	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(window);

	ImGui::Begin("Transform Inspector", &active);
	ImGui::Text("Components:");

	ImGui::End();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

	//SDL_RenderPresent(polygon->renderer);
}