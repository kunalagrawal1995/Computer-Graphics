#include "gl_framework.hpp"
#include "glm/vec3.hpp"

extern GLfloat xrot,yrot,zrot;
extern glm::vec3 trans;
extern GLint state;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      state = 0;
  else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      state = 1;
  
  else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      state = 2;
  
  else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      state = 3;
  
  else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      state = 4;
  
  else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    yrot -= 1.0;
  else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    yrot += 1.0;
  else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    xrot += 1.0;
  else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    xrot -= 1.0;
  else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
    zrot += 1.0;
  else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
    zrot -= 1.0;
  else if(key == GLFW_KEY_A && action == GLFW_PRESS)
    trans[0] += 0.1;
  else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    trans[0] -= 0.1;
  else if(key == GLFW_KEY_W && action == GLFW_PRESS)
    trans[1] += 0.1;
  else if(key == GLFW_KEY_S && action == GLFW_PRESS)
    trans[1] -= 0.1;
  else if(key == GLFW_KEY_Z && action == GLFW_PRESS)
    trans[2] += 0.1;
  else if(key == GLFW_KEY_X && action == GLFW_PRESS)
    trans[2] -= 0.1;
      
}
};  
  



