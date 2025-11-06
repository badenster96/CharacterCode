#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <memory>
#include "SceneManager.h"
#include "Level.h"

// Globals
std::unique_ptr<SceneManager> gSceneManager;
bool gFullscreen = false;
RECT gWindowRect = {};
HWND gHwnd = nullptr;
HDC gHdc = nullptr;

// --- Helper to resize OpenGL viewport ---
void ResizeViewport(int width, int height)
{
    if (height == 0) height = 1; // prevent divide by zero

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / (float)height, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Forward declarations
bool CreateGLWindow(HINSTANCE hInstance, int width, int height, const char* title, HWND& outHWnd, HDC& outHDC);

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;

        case VK_F1: // Toggle fullscreen
            gFullscreen = !gFullscreen;
            if (gFullscreen)
            {
                GetWindowRect(hwnd, &gWindowRect); // Save original window rect
                SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
                SetWindowPos(hwnd, HWND_TOP, 0, 0,
                             GetSystemMetrics(SM_CXSCREEN),
                             GetSystemMetrics(SM_CYSCREEN),
                             SWP_FRAMECHANGED | SWP_SHOWWINDOW);

                ResizeViewport(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
            }
            else
            {
                SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
                SetWindowPos(hwnd, HWND_TOP,
                             gWindowRect.left, gWindowRect.top,
                             gWindowRect.right - gWindowRect.left,
                             gWindowRect.bottom - gWindowRect.top,
                             SWP_FRAMECHANGED | SWP_SHOWWINDOW);

                ResizeViewport(gWindowRect.right - gWindowRect.left,
                               gWindowRect.bottom - gWindowRect.top);
            }
            break;
        }
        break;

    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        ResizeViewport(width, height);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Forward input messages to SceneManager
    if (gSceneManager)
        gSceneManager->handleWinMsg(hwnd, message, wParam, lParam);

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    // Create OpenGL window
    if (!CreateGLWindow(hInstance, 800, 600, "CharacterCode Engine", gHwnd, gHdc))
        return -1;

    // Lock mouse to window
    RECT rc;
    GetClientRect(gHwnd, &rc);
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    MapWindowPoints(gHwnd, nullptr, (POINT*)&rc, 2);
    ClipCursor(&rc);
    ShowCursor(FALSE);

    // OpenGL setup
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // SceneManager setup
    gSceneManager = std::make_unique<SceneManager>();
    gSceneManager->getInputs()->setWindowCenter(width, height);
    gSceneManager->addScene("Level1", new Level());
    gSceneManager->switchTo("Level1");

    // Call init() on Level
    Level* lvl = dynamic_cast<Level*>(gSceneManager->getCurrentScene());
    if (lvl) {
        //lvl->attachSystems(gSceneManager->getInputs(), gSceneManager->getCamera());
        lvl->init();
    }

    // Set initial viewport
    ResizeViewport(800, 600);

    LARGE_INTEGER freq, lastTime;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&lastTime);

    // Main loop
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);
            float dt = (float)(currentTime.QuadPart - lastTime.QuadPart) / (float)freq.QuadPart;
            lastTime = currentTime;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            gSceneManager->update(dt); // ~60 FPS
            gSceneManager->draw();

            SwapBuffers(gHdc);
        }
    }

    // Release mouse
    ClipCursor(nullptr);
    ShowCursor(TRUE);

    return (int)msg.wParam;
}

// OpenGL window creation (unchanged)
bool CreateGLWindow(HINSTANCE hInstance, int width, int height, const char* title, HWND& outHWnd, HDC& outHDC)
{
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OpenGLWindowClass";

    if (!RegisterClass(&wc))
    {
        MessageBox(nullptr, "RegisterClass failed", "Error", MB_OK);
        return false;
    }

    outHWnd = CreateWindow(
        "OpenGLWindowClass",
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr, nullptr, hInstance, nullptr);

    if (!outHWnd)
    {
        MessageBox(nullptr, "CreateWindow failed", "Error", MB_OK);
        return false;
    }

    outHDC = GetDC(outHWnd);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pf = ChoosePixelFormat(outHDC, &pfd);
    if (!pf)
    {
        MessageBox(nullptr, "ChoosePixelFormat failed", "Error", MB_OK);
        return false;
    }

    if (!SetPixelFormat(outHDC, pf, &pfd))
    {
        MessageBox(nullptr, "SetPixelFormat failed", "Error", MB_OK);
        return false;
    }

    HGLRC hRC = wglCreateContext(outHDC);
    if (!hRC)
    {
        MessageBox(nullptr, "wglCreateContext failed", "Error", MB_OK);
        return false;
    }

    if (!wglMakeCurrent(outHDC, hRC))
    {
        MessageBox(nullptr, "wglMakeCurrent failed", "Error", MB_OK);
        return false;
    }

    return true;
}
