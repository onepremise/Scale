#ifndef __sseDisplayManager__
#define __sseDisplayManager__

#include "sseInclude.hpp"
#include "sseLog.h"

enum FONTI18NMODE {
	RENDER_LATIN1,
	RENDER_UTF8,
	RENDER_UNICODE
};

#define DEFAULT_PTSIZE	18
#define NUM_COLORS      256

class sseDisplayManager
{
public:
	static sseDisplayManager *Instance();
	~sseDisplayManager();

protected:
	sseDisplayManager();

public:
	void InitializeWindow();
	void ConfigurePixelFormat(void);
	void CreateSDLWindow(void);
	void Clear(void);
	void onMove(int xPos, int yPos);
	void onFocus(int focusted);
	void onClose(void);
	void onIconify(int iconified);
	void onResize(int width, int height);
	void onFrameBufferResize(int width, int height);
	void onRefresh(void);
	void Flip(void);
	void SwitchToFullScreen(void);
	void GetVideoInfo(void);
	GLFWwindow *GetWindow() {return m_window;}
	int  GetWidth(void) {return m_width;}
	int  GetHeight(void) {return m_height;}
	int  GetDepth(void) {return m_depth;}
	int  GetCenterX(void) {return m_iCenterX;}
	int  GetCenterY(void) {return m_iCenterY;}
	void SetCursorCenter(void);
	void SetCursor(int x, int y);
	void SetProjectionMatrix(float zDistance=1);

private:
	void InstallHooks(GLFWwindow* window);

    inline static auto onResizeCallback(
        GLFWwindow *win,
        int w,
        int h) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onResize(w, h);
    }

    inline static auto onFrameBuffResizeCallback(
        GLFWwindow *win,
        int w,
        int h) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onFrameBufferResize(w, h);
    }

    inline static auto onRefreshCallback(
    	GLFWwindow *win) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onRefresh();
    }

    inline static auto onMoveCallback(
    	GLFWwindow *win, int x, int y) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onMove(x, y);
    }

    inline static auto onFocusCallback(
    	GLFWwindow *win, int focused) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onFocus(focused);
    }

    inline static auto onCloseCallback(
    	GLFWwindow *win) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onClose();
    }

    inline static auto onIconifyCallback(
    	GLFWwindow *win, int iconified) -> void {
    	sseDisplayManager *window = static_cast<sseDisplayManager*>(glfwGetWindowUserPointer(win));
        window->onIconify(iconified);
    }

private:
	static sseDisplayManager *_instance;
	sseLog *m_log;

private:
	GLFWwindow* m_window;

	int m_width;
	int m_height;
	int m_depth;

	double m_nearClip, m_farClip;

	float m_zDistance;

	int m_iCenterX;
	int m_iCenterY;

	GLuint m_texture;
};

#endif
