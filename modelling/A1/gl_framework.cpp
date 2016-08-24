#include "gl_framework.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

extern GLfloat xrot,yrot,zrot,model_z;
extern glm::vec3 trans;
extern int mode;
extern double *x,*y;
extern std::vector<glm::vec4> model_positions,model_colors;

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

  bool compare(glm::vec4 const & a,glm::vec4 const& b){
    if(a[0]<b[0]) return true;
    else if(a[0]==b[0]){
      if(a[1]<b[1]) return true;
      else if(a[1]==b[1]){
        if(a[2]<b[2]) return true;
        else return false;
      }
    }
    return false;
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
    else if (key == GLFW_KEY_M && action == GLFW_PRESS){
      xrot=yrot=zrot=model_z=0;
      trans[0]=trans[1]=trans[2]=0.0;
      std::cout<<"modelling mode"<<std::endl;
      mode=0;
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS){
      std::cout<<"inspection mode"<<std::endl;
      mode=1;
    }
    // inspection mode
    if(mode==1){
      if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
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
      else if(key == GLFW_KEY_L && action == GLFW_PRESS){
        std::cout<<"Please enter the file name: ";
        std::string filename;
        std::cin>>filename;
        filename+=".raw";
        char * name=&filename[0];
        std::ifstream file_obj;
        file_obj.open(name);
        if(file_obj.is_open()){
          xrot=yrot=zrot=model_z=0;
          trans[0]=trans[1]=trans[2]=0.0;
          model_positions.clear();
          model_colors.clear();
          float inp_x,inp_y,inp_z,inp_r,inp_g,inp_b;
          glm::vec4 inp_pos,inp_color;
          while(file_obj>>inp_x>>inp_y>>inp_z>>inp_r>>inp_g>>inp_b){
            inp_pos[0] = inp_x;
            inp_pos[1] = inp_y;
            inp_pos[2] = inp_z;
            inp_pos[3] = 1.0f;
            inp_color[0] = inp_r;
            inp_color[1] = inp_g;
            inp_color[2] = inp_b;
            inp_color[3] = 1.0f;
            model_positions.push_back(inp_pos);
            model_colors.push_back(inp_color);
          }
          std::cout<<name<<" is now loaded."<<std::endl;
          file_obj.close();
        }
        else{
          std::cout<<"No file exists with name "<< filename<<std::endl;
        }
      }
      else if(key == GLFW_KEY_R && action == GLFW_PRESS){
        std::vector<glm::vec4> positions_temp=model_positions;
        sort(positions_temp.begin(),positions_temp.end(),compare);
        int count=0;
        std::vector<glm::vec4> temp;
        int size=positions_temp.size();
        if(size>0) temp.push_back(positions_temp[0]);
        for(int i=1;i<size;i++){
          if(positions_temp[i]!=positions_temp[i-1]) temp.push_back(positions_temp[i]);
        }
        size=temp.size();
        trans[0]=trans[1]=trans[2]=0;
        for(int i=0;i<size;i++){
          trans[0]-=temp[i][0];
          trans[1]-=temp[i][1];
          trans[2]-=temp[i][2];
        }
        if(size>0){
          trans[0]/=size;
          trans[1]/=size;
          trans[2]/=size;
        }

      }
    }

    //modelling mode
    else if(mode==0){
      if(key == GLFW_KEY_T && action == GLFW_PRESS)
        model_z += 0.1;
      else if(key == GLFW_KEY_H && action == GLFW_PRESS)
        model_z -= 0.1;
      else if(key == GLFW_KEY_C && action == GLFW_PRESS){
        model_positions.clear();
        model_colors.clear();
        xrot=yrot=zrot=model_z=0;
        trans[0]=trans[1]=trans[2]=0.0;
      }
      else if(key == GLFW_KEY_K && action == GLFW_PRESS){
        std::cout<<"Please enter the file name: ";
        std::string filename;
        std::cin>>filename;
        filename+=".raw";
        char * name=&filename[0];
        std::ofstream file_obj;
        file_obj.open(name);
        for(int i=0;i<model_positions.size();i++){
          file_obj<<model_positions[i][0]<<" "<<model_positions[i][1]<<" "<<model_positions[i][2]<<" "<<model_colors[i][0]<<" "<<model_colors[i][1]<<" "<<model_colors[i][2]<<std::endl;
        }
        std::cout<<name<<" is successfully saved."<<std::endl;
        file_obj.close();
      }
      else if(key == GLFW_KEY_L && action == GLFW_PRESS){
        std::cout<<"Please enter the file name: ";
        std::string filename;
        std::cin>>filename;
        filename+=".raw";
        char * name=&filename[0];
        std::ifstream file_obj;
        file_obj.open(name);
        if(file_obj.is_open()){
          xrot=yrot=zrot=model_z=0;
          trans[0]=trans[1]=trans[2]=0.0;
          model_positions.clear();
          model_colors.clear();
          float inp_x,inp_y,inp_z,inp_r,inp_g,inp_b;
          glm::vec4 inp_pos,inp_color;
          while(file_obj>>inp_x>>inp_y>>inp_z>>inp_r>>inp_g>>inp_b){
            inp_pos[0] = inp_x;
            inp_pos[1] = inp_y;
            inp_pos[2] = inp_z;
            inp_pos[3] = 1.0f;
            inp_color[0] = inp_r;
            inp_color[1] = inp_g;
            inp_color[2] = inp_b;
            inp_color[3] = 1.0f;
            model_positions.push_back(inp_pos);
            model_colors.push_back(inp_color);
          }
          std::cout<<name<<" is now loaded."<<std::endl;
          file_obj.close();
        }
        else{
          std::cout<<"No file exists with name "<< filename<<std::endl;
        }
      }
    }
  }

  void mouse_callback(GLFWwindow* window, int key, int action, int mods){
    //modelling mode
    if(mode==0){
        if(key == GLFW_MOUSE_BUTTON_LEFT && action== GLFW_PRESS && mods == 0){
          std::cout<<"no - popped"<<std::endl;
        //draw a point, store a vertex
        glfwGetCursorPos(window, x, y);
        double x_norm = (*x-256)/128;
        double y_norm = (256- *y)/128;
        model_positions.push_back(glm::vec4(float(x_norm),float(y_norm),model_z,1.0f));
        model_colors.push_back(glm::vec4(0.5f,0.4f,0.3f,1.0f));
        std::cout<< x_norm <<" "<< y_norm << " "<<model_z<<std::endl;
        //std::cout<model_positions.x<<" "<<model_positions.y<<" "<<model_positions.z<<std::endl;
        }
        else if(key== GLFW_MOUSE_BUTTON_LEFT && action== GLFW_PRESS && mods==1){
          std::cout<<"popped"<<std::endl;
          model_positions.pop_back();
          model_colors.pop_back();
        }
    }

  }
};  
  


