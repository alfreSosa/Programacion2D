#ifndef UGINE_SCREEN_H
#define UGINE_SCREEN_H

#include "string.h"
#include "types.h"

//const float zerof = 0.0f; //Preguntar si quiero zerof

class Screen {
public:
    static Screen& Instance();
	
	// Pantalla
    virtual void Open(uint16 width, uint16 height, bool fullscreen);
    virtual void Close();
    virtual bool IsOpened() const;
    virtual void SetTitle(const String& title);
    virtual void Refresh();
    virtual uint16 GetWidth() const { return m_width; }
    virtual uint16 GetHeight() const { return m_height; }
    virtual uint16 GetDesktopWidth() const;
    virtual uint16 GetDesktopHeight() const;

	// Temporizador
    double ElapsedTime() const { return m_elapsed; }

	// Input
    virtual double GetMouseX() const { return m_mousex; }
    virtual double GetMouseY() const { return m_mousey; }
    virtual bool MouseButtonPressed(int button) const;
    virtual bool KeyPressed(int key) const;
protected:
    Screen();
    virtual ~Screen();
private:
    static Screen* m_screen;

    bool m_opened;
    int m_width, m_height;
    double m_mousex, m_mousey;
    double m_lastTime;
    double m_elapsed;
    struct GLFWwindow* m_mainWindow;
    struct GLFWmonitor* m_mainMonitor;

    static void CloseCallback(GLFWwindow* window);
public:
    static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif
