#pragma once
#include <windows.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        // --- Keyboard Functions ---
        // These now use the 'wParam' member variable
        void keyPressed();
        void keyUp();

        // --- Mouse Functions ---
        void mouseEventDown(double x, double y);
        void mouseEventUp();
        void mouseWheel(double delta);
        void mouseMove(double x, double y);

        // --- Keyboard State (for Scene to read) ---
        bool isMovingLeft;
        bool isMovingRight;
        bool isMovingUp;
        bool isMovingDown;
        bool isZoomingIn;  // New
        bool isZoomingOut; // New

        // --- Mouse State (for Scene to read) ---
        double prev_Mouse_X;
        double prev_Mouse_Y;
        double mouseDeltaX; // New
        double mouseDeltaY; // New
        double wheelDelta;  // New

        bool Mouse_Translate;
        bool Mouse_Rotate;

        WPARAM wParam; // Scene will set this

    protected:

    private:
};