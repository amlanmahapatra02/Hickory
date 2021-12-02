#include "hkpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hickory
{

	

	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		:m_WindowHandle(windowhandle)
	{
		HK_CORE_ASSERT(m_WindowHandle, "Window Handle was null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HK_CORE_ASSERT("Failed to initialize Glad! ", status);

		HK_CORE_INFO("Hardware Info : ");
		HK_CORE_INFO("		GPU : {0} ", glGetString(GL_VENDOR));
		HK_CORE_INFO("		Renderer : {0} ", glGetString(GL_RENDERER));
		HK_CORE_INFO("		Version : {0} ", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
