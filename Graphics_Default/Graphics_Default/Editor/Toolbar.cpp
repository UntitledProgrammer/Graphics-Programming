#include "Toolbar.h"
#include"Windows.h"
#include"Hierarchy.h"

Toolbar::Toolbar(SDL_Window* window, SDL_GLContext* context) : window(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init();
}

Toolbar::~Toolbar()
{

}

void Toolbar::Update()
{
    //Load new frame.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    //Draw window.
    ImGui::Begin("Toolbar", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT / 12));
    ImGui::SetWindowPos(ImVec2(0, 0));
    for (int i = 0; i < windows.size(); i++)
    {
        if (ImGui::Button(windows[i]->name.c_str())) { windows[i]->active = !windows[i]->active; } //If button is clicked, flip the value of active.
        ImGui::SameLine();
    }

    for (int i = 0; i < windows.size(); i++)
    {
        if (windows[i]->active) { windows[i]->Render(); } //If window is active, render window.
    }
    ImGui::End();

    //Render frame.
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Toolbar::LoadDefault()
{
    windows.push_back(new Inspector());
    windows.push_back(new Menu());
    windows.push_back(new Hierarchy());
}