/*
  CSX75 Tutorial 3

  A program which opens a window and draws the "color cube."

  Use the arrow keys and +/-, PgUp,PgDn, Home,End, Ins,Del 
  keys to make the cube move.

  Use w/W to toggle between wireframe and solid models
  Use c/C to toggle backface culling on/off

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Parag Chaudhuri, 2015
*/


#include "03_colorcube_rotate.hpp"

GLuint shaderProgram;
GLuint vbo, vao;

glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 translated_matrix;
glm::mat4 move_to_origin;
glm::mat4 move_back_to_centroid;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;
glm::vec3 centroid(0.0,0.0,0.0);

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

void initBuffersGL(void)
{
  //Ask GL for a Vertex Attribute Object (vao)
  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);

  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);
  //Set it as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBufferData (GL_ARRAY_BUFFER, model_positions.size()*sizeof(glm::vec4)+ model_colors.size()*sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, model_positions.size()*sizeof(glm::vec4), &model_positions[0]);
  glBufferSubData( GL_ARRAY_BUFFER, model_positions.size()*sizeof(glm::vec4),model_colors.size()*sizeof(glm::vec4), &model_colors[0]);
  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("03_vshader.glsl");
  std::string fragment_shader_file("03_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // set up vertex arrays
  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  
  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(model_positions.size()*sizeof(glm::vec4)) );

  if(mode==1){
    std::vector<glm::vec4> positions_temp=model_positions;
    std::sort(positions_temp.begin(),positions_temp.end(),compare);
    int count=0;
    std::vector<glm::vec4> temp;
    int size=model_positions.size();
    if(size>0) temp.push_back(positions_temp[0]);
    for(int i=1;i<size;i++){
      if(positions_temp[i]!=positions_temp[i-1]) temp.push_back(positions_temp[i]);
    }
    size=temp.size();
    centroid[0]=centroid[1]=centroid[2]=0;
    for(int i=0;i<size;i++){
      centroid[0]+=temp[i][0];
      centroid[1]+=temp[i][1];
      centroid[2]+=temp[i][2];
    }
    if(size>0){
      centroid[0]/=size;
      centroid[1]/=size;
      centroid[2]/=size;
    }
    //std::cout<<centroid[0]<<" "<<centroid[1]<<" "<<centroid[2]<<" "<<trans[0]<<" "<<trans[1]<<" "<<trans[2]<<std::endl;
    move_back_to_centroid = glm::translate(glm::mat4(1.0f), centroid);
    translated_matrix = glm::translate(glm::mat4(1.0f), trans);
    rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
    centroid[0]=-centroid[0];
    centroid[1]=-centroid[1];
    centroid[2]=-centroid[2];
    move_to_origin = glm::translate(glm::mat4(1.0f),centroid);
    ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);

    modelview_matrix = ortho_matrix * translated_matrix * move_to_origin * rotation_matrix * move_back_to_centroid;
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    // Draw 
    glDrawArrays(GL_TRIANGLES, 0, model_positions.size());
  }
  else if(mode==0){  
        ortho_matrix = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
        modelview_matrix = ortho_matrix;
        glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
        glDrawArrays(GL_TRIANGLES, 0, model_positions.size());
  }
  
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Mouse callback
  glfwSetMouseButtonCallback(window, csX75::mouse_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

