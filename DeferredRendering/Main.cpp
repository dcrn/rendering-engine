#include <glbinding/gl41core/gl.h>
#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
	{
		return 1;
	}
	
	glfwDefaultWindowHints();
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Rendering Demo", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return 1;
	}

	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	return 0;
}
