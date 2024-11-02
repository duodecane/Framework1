#include "App.h"



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    static int ScrollDelta = 0;
    if (msg == WM_MOUSEWHEEL) {
        ScrollDelta += GET_WHEEL_DELTA_WPARAM(wParam);
        for (; ScrollDelta > WHEEL_DELTA; ScrollDelta -= WHEEL_DELTA)
            App->Scroll += 1;
        for (; ScrollDelta < 0; ScrollDelta += WHEEL_DELTA)
            App->Scroll -= 1;
    }



    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

    switch (msg)
    {
    case WM_SIZE:
        if (App->Render->RenderDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            App->Render->DirectXParams.BackBufferWidth = LOWORD(lParam);
            App->Render->DirectXParams.BackBufferHeight = HIWORD(lParam);
            App->Render->Reset();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CApp::Exit() {
    exit(0);
}
std::vector<int> CApp::GetInputCharacters() {
    ImGui::GetIO().WantTextInput = true;
    std::vector<int> A;
    if (ImGui::GetIO().InputQueueCharacters.Size > 0) {
        for (auto c : ImGui::GetIO().InputQueueCharacters) {
            A.push_back(c);
        }
    }

    return A;
    /*
    std::vector<int> A;
    bool Capital = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;

    if (KeyToggled(VK_RETURN))
        A.push_back(VK_RETURN);

    if (KeyToggled(VK_ESCAPE))
        A.push_back(VK_ESCAPE);

    if (KeyToggled(VK_BACK))
        A.push_back(VK_BACK);

    if (KeyToggled(VK_SPACE))
        A.push_back(VK_SPACE);

    for (int i = 0; i < 10; i++) {
        if (KeyToggled(48 + i))
            A.push_back(48 + i);
    }
    for (int i = 0; i <= 25; i++) {
        if (KeyToggled(65 + i))
            if (KeyPressed(VK_LSHIFT) || KeyPressed(VK_RSHIFT) || Capital)
                A.push_back(65 + i);
            else
                A.push_back(97 + i);
    }

    return A;*/
}
void CApp::Init() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    SetProcessDPIAware();


    ScreenSize = Vec2(1200, 900);

    DefaultSearchFolder = "";
    {
        TCHAR* path = new TCHAR[256];
        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
        {
            DefaultSearchFolder = std::string(path);// + ("\\.NMRProjects");
        }
    }

    
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
    wcex.lpszClassName = "Framework";
    wcex.lpszMenuName = nullptr;
    wcex.hInstance = GetModuleHandleA(NULL);
    wcex.lpfnWndProc = WndProc;
    RegisterClassEx(&wcex);
    Window = CreateWindowA("Framework", "Framework", CW_USEDEFAULT,
        (1920 / 2) - ScreenSize.x / 2, (1080 / 2) - ScreenSize.y / 2, ScreenSize.x, ScreenSize.y, nullptr, nullptr, GetModuleHandleA(NULL), nullptr);
    // SetWindowLongW(Window, GWL_EXSTYLE, 0);

    if (!App->Render->CreateDeviceD3D(Window)) {
        App->Render->Release();
        UnregisterClass(wcex.lpszClassName, wcex.hInstance);
        return;
    }


    ShowWindow(Window, SW_SHOW);
    UpdateWindow(Window);

    // Setup Dear ImGui context
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; //crutial for not leaving the imgui.ini file
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX9_Init(Render->RenderDevice);


    Render::Initialize();
    ShouldExit = false;
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        Curtime = (float)(clock());

        if (LastLoopTime == -1.f)
            LastLoopTime = Curtime;


        Interval = Curtime - LastLoopTime;




        LastLoopTime = Curtime;





        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        Render::DoRender();

        ImGui::EndFrame();

        Render->RenderDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0);
        if (Render->RenderDevice->BeginScene() >= 0)
        {
            ImGui::Render();

            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());




            Render->RenderDevice->EndScene();
        }


        HRESULT result = Render->RenderDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && Render->RenderDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            Render->Reset();
        }
        if (ShouldExit) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    Render->Release();
    DestroyWindow(Window);
    UnregisterClass(wcex.lpszClassName, wcex.hInstance);
}
void CApp::UpdateKeyStates() {

    PrevMP = Vec2(ImGui::GetIO().MousePosPrev.x, ImGui::GetIO().MousePosPrev.y);
    MP = Vec2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);

    std::copy(KeyStates, KeyStates + 255, OldKeyStates);
    for (unsigned int i = 0; i < 255; i++)
        KeyStates[i] = GetAsyncKeyState(i);

    Mouse1Click = KeyToggled(VK_LBUTTON);
    Mouse1Press = KeyPressed(VK_LBUTTON);
}


void CApp::RenderScenes() {
    Render::FilledRect(0, 0, ScreenSize.x, ScreenSize.y, Col(0,0,0));
   //everything here
}

CApp* App = new CApp();