#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <fstream>

extern GLfloat c_xrot,c_yrot,c_zrot,c_zpos;
extern GLint light_flag1,light_flag2;
extern bool enable_perspective;
extern bool playback;
extern std::vector< std::vector<GLfloat> > keyframes;
extern csX75::HNode* r2d2_node1, *r2d2_node2, *r2d2_node3, *r2d2_node4, *r2d2_node5, *r2d2_node6, *r2d2_node7, *r2d2_node8;
extern csX75::HNode* c3po_node1, *c3po_node2, *c3po_node3, *c3po_node4, *c3po_node5, *c3po_node6, *c3po_node7, *c3po_node8,*c3po_node9,*c3po_node10,*c3po_node11,*c3po_node12,*c3po_node13,*c3po_node14;
extern csX75::HNode* curr_node, *c3po_root_node, *r2d2_root_node, *curr_root;
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

    //r2d2 keys
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node1;
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node2; 
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node3;
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node4;
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node5;
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node6;
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node7;
      curr_root = r2d2_root_node;
    }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS && mods == 0){
      curr_node = r2d2_node8;
      curr_root = r2d2_root_node;
    }

    //c3po keys
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node1;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node2;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node3;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node4;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node5;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node6;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node9;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node10;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node11;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node12;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node7;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node8;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node13;
      curr_root = c3po_root_node;
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS && mods == 1){
      curr_node = c3po_node14; 
      curr_root = c3po_root_node;
    }

    //scaling keys
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && mods == 1)
      curr_node->dec_sy();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && mods == 1)
      curr_node->inc_sy();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && mods == 1)
      curr_node->dec_sx();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS && mods == 1)
      curr_node->inc_sx();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && mods == 1)
      curr_node->dec_sz();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && mods == 1)
      curr_node->inc_sz();
 
    //rotation keys
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && mods == 0)
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && mods == 0)
      curr_node->inc_ry();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && mods == 0)
      curr_node->dec_rx();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS && mods == 0)
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && mods == 0)
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && mods == 0)
      curr_node->inc_rz();

    //root node translations
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
      curr_root->inc_tx();
    else if (key == GLFW_KEY_F && action == GLFW_PRESS)
      curr_root->dec_tx();
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
      curr_root->inc_ty();
    else if (key == GLFW_KEY_G && action == GLFW_PRESS)
      curr_root->dec_ty();
    else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
      curr_root->inc_tz();
    else if (key == GLFW_KEY_H && action == GLFW_PRESS)
      curr_root->dec_tz();

    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;

    //camera rotations
    else if (key == GLFW_KEY_A  && action == GLFW_REPEAT)
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  && action == GLFW_REPEAT)
      c_yrot += 1.0;
    else if (key == GLFW_KEY_S  && action == GLFW_REPEAT)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_W  && action == GLFW_REPEAT)
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_REPEAT)
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  && action == GLFW_REPEAT)
      c_zrot += 1.0;

  //zoom in/out
    else if (key == GLFW_KEY_Z && action == GLFW_REPEAT && mods==0)
      c_zpos -= 0.1;
    else if (key == GLFW_KEY_Z && action == GLFW_REPEAT && mods==1)
      c_zpos += 0.1;

    //turn lights on/off
    else if (key == GLFW_KEY_K && action == GLFW_PRESS){
      if(light_flag1==1)  light_flag1=0;
      else light_flag1=1;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS){
      if(light_flag2==1)  light_flag2=0;
      else light_flag2=1;
    }


    else if(key == GLFW_KEY_M && action == GLFW_PRESS){
      std::ofstream file_obj;
      file_obj.open("keyframes.txt", std::ios::out | std::ios::app);
      if(file_obj.is_open()){
        file_obj<<light_flag1<<" "<<light_flag2<<" "<<c_xrot<<" "<<c_yrot<<" "<<c_zrot<<" "<<c_zpos<<" "<<
        r2d2_root_node->get_tx()<<" "<<r2d2_root_node->get_ty()<<" "<<r2d2_root_node->get_tz()<<" "<<
        r2d2_node1->get_rx()<<" "<<r2d2_node1->get_ry()<<" "<<r2d2_node1->get_rz()<<" "<<
        r2d2_node2->get_rx()<<" "<<r2d2_node2->get_ry()<<" "<<r2d2_node2->get_rz()<<" "<<
        r2d2_node3->get_rx()<<" "<<r2d2_node3->get_ry()<<" "<<r2d2_node3->get_rz()<<" "<<
        r2d2_node4->get_rx()<<" "<<r2d2_node4->get_ry()<<" "<<r2d2_node4->get_rz()<<" "<<
        r2d2_node5->get_rx()<<" "<<r2d2_node5->get_ry()<<" "<<r2d2_node5->get_rz()<<" "<<
        r2d2_node6->get_rx()<<" "<<r2d2_node6->get_ry()<<" "<<r2d2_node6->get_rz()<<" "<<
        r2d2_node7->get_rx()<<" "<<r2d2_node7->get_ry()<<" "<<r2d2_node7->get_rz()<<" "<<
        r2d2_node8->get_rx()<<" "<<r2d2_node8->get_ry()<<" "<<r2d2_node8->get_rz()<<" "<<
        c3po_root_node->get_tx()<<" "<<c3po_root_node->get_ty()<<" "<<c3po_root_node->get_tz()<<" "<<
        c3po_node1->get_rx()<<" "<<c3po_node1->get_ry()<<" "<<c3po_node1->get_rz()<<" "<<
        c3po_node2->get_rx()<<" "<<c3po_node2->get_ry()<<" "<<c3po_node2->get_rz()<<" "<<
        c3po_node3->get_rx()<<" "<<c3po_node3->get_ry()<<" "<<c3po_node3->get_rz()<<" "<<
        c3po_node4->get_rx()<<" "<<c3po_node4->get_ry()<<" "<<c3po_node4->get_rz()<<" "<<
        c3po_node5->get_rx()<<" "<<c3po_node5->get_ry()<<" "<<c3po_node5->get_rz()<<" "<<
        c3po_node6->get_rx()<<" "<<c3po_node6->get_ry()<<" "<<c3po_node6->get_rz()<<" "<<
        c3po_node7->get_rx()<<" "<<c3po_node7->get_ry()<<" "<<c3po_node7->get_rz()<<" "<<
        c3po_node8->get_rx()<<" "<<c3po_node8->get_ry()<<" "<<c3po_node8->get_rz()<<" "<<
        c3po_node9->get_rx()<<" "<<c3po_node9->get_ry()<<" "<<c3po_node9->get_rz()<<" "<<
        c3po_node10->get_rx()<<" "<<c3po_node10->get_ry()<<" "<<c3po_node10->get_rz()<<" "<<
        c3po_node11->get_rx()<<" "<<c3po_node11->get_ry()<<" "<<c3po_node11->get_rz()<<" "<<
        c3po_node12->get_rx()<<" "<<c3po_node12->get_ry()<<" "<<c3po_node12->get_rz()<<" "<<
        c3po_node13->get_rx()<<" "<<c3po_node13->get_ry()<<" "<<c3po_node13->get_rz()<<" "<<
        c3po_node14->get_rx()<<" "<<c3po_node14->get_ry()<<" "<<c3po_node14->get_rz()<<std::endl;
        file_obj.close();
        std::cout<<"keyframe saved to keyframes.txt"<<std::endl;
      }
      else {
        std::cerr<<"unable to open file keyframes.txt, write not made."<<std::endl;
      }
    }

    //playback
    else if(key == GLFW_KEY_N && action == GLFW_PRESS){
    	//initialize keyframes vector by reading keyframes.txt
    	keyframes.clear();
    	std::ifstream file_obj;
      	file_obj.open("keyframes.txt");
      	std::vector <GLfloat> temp(78);
      	if(file_obj.is_open()){
      		while(file_obj>>temp[0]){
	      		for(int i = 1; i<78;i++){
	      			file_obj>>temp[i];
	      		}
	      		keyframes.push_back(temp);
	      	}
	      	file_obj.close();
      	}
      	else{
      		std::cerr<<"unable to open file"<<std::endl;
      	}

    	glfwSetTime(0);
    	//playback started
    	playback = true;
    }
  }
};  
  


