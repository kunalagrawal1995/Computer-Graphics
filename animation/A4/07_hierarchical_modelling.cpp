/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
*/


#include "07_hierarchical_modelling.hpp"
#include "texture.hpp"

double PI=3.14159265;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint shader_light_flag1, shader_light_flag2;

unsigned char *pRGB;
int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = 512;

void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"frames/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}

void load(std::string model, std::vector<glm::vec4> &model_positions, std::vector<glm::vec4> &model_colors, std::vector<glm::vec4> &model_normals, std::vector<glm::vec2> &model_tex_coords){
  model="./raw_files/"+model+".raw";
  char * name=&model[0];
  std::ifstream file_obj;
  file_obj.open(name);
  if(file_obj.is_open()){
    model_positions.clear();
    model_colors.clear();
    glm::vec4 inp_pos,inp_color,inp_normal;
    glm::vec2 inp_tex;
    inp_pos[3] = 1.0f;
    inp_color[3] = 1.0f;
    while(file_obj>>inp_pos[0]>>inp_pos[1]>>inp_pos[2]>>inp_color[0]>>inp_color[1]>>inp_color[2]>>inp_normal[0]>>inp_normal[1]>>inp_normal[2]>>inp_tex[0]>>inp_tex[1]){
      model_positions.push_back(inp_pos);
      model_colors.push_back(inp_color);
      model_normals.push_back(inp_normal);
      model_tex_coords.push_back(inp_tex);
    }
    std::cout<<name<<" is now loaded."<<std::endl;
    file_obj.close(); 
  }
  else{
    std::cout<<"No file exists with name "<< name<<std::endl;
  }

} // load cosed

//-----------------------------------------------------------------

void set_parameters(int keyframe_number, int interpolation_num){
	std::vector<GLfloat> interpolated_vals = keyframes[keyframe_number];
	for(int i = 0; i<78;i++){
		interpolated_vals[i] += interpolation_num*((keyframes[keyframe_number+1][i]-keyframes[keyframe_number][i])/(1.0*num_interpolations));
	}
	//assign values
	int k=0;
	if(interpolated_vals[k++]<0.5){
		light_flag1=0;
	}
	else{
		light_flag1=1;
	}
	if(interpolated_vals[k++]<0.5){
		light_flag2=0;
	}
	else{
		light_flag2=1;
	}
	c_xrot=interpolated_vals[k++];
	c_yrot=interpolated_vals[k++];
	c_zrot=interpolated_vals[k++];
	c_zpos=interpolated_vals[k++];
  r2d2_root_node->change_parameters(interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_root_node->get_rx(),r2d2_root_node->get_ry(),r2d2_root_node->get_rz(),r2d2_root_node->get_sx(),r2d2_root_node->get_sy(),r2d2_root_node->get_sz());
	k+=3; r2d2_node1->change_parameters(r2d2_node1->get_tx(),r2d2_node1->get_ty(),r2d2_node1->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node1->get_sx(),r2d2_node1->get_sy(),r2d2_node1->get_sz());
	k+=3; r2d2_node2->change_parameters(r2d2_node2->get_tx(),r2d2_node2->get_ty(),r2d2_node2->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node2->get_sx(),r2d2_node2->get_sy(),r2d2_node2->get_sz());
	k+=3; r2d2_node3->change_parameters(r2d2_node3->get_tx(),r2d2_node3->get_ty(),r2d2_node3->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node3->get_sx(),r2d2_node3->get_sy(),r2d2_node3->get_sz());
	k+=3; r2d2_node4->change_parameters(r2d2_node4->get_tx(),r2d2_node4->get_ty(),r2d2_node4->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node4->get_sx(),r2d2_node4->get_sy(),r2d2_node4->get_sz());
	k+=3; r2d2_node5->change_parameters(r2d2_node5->get_tx(),r2d2_node5->get_ty(),r2d2_node5->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node5->get_sx(),r2d2_node5->get_sy(),r2d2_node5->get_sz());
	k+=3; r2d2_node6->change_parameters(r2d2_node6->get_tx(),r2d2_node6->get_ty(),r2d2_node6->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node6->get_sx(),r2d2_node6->get_sy(),r2d2_node6->get_sz());
	k+=3; r2d2_node7->change_parameters(r2d2_node7->get_tx(),r2d2_node7->get_ty(),r2d2_node7->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node7->get_sx(),r2d2_node7->get_sy(),r2d2_node7->get_sz());
	k+=3; r2d2_node8->change_parameters(r2d2_node8->get_tx(),r2d2_node8->get_ty(),r2d2_node8->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],r2d2_node8->get_sx(),r2d2_node8->get_sy(),r2d2_node8->get_sz());
	k+=3; c3po_root_node->change_parameters(interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_root_node->get_rx(),c3po_root_node->get_ry(),c3po_root_node->get_rz(),c3po_root_node->get_sx(),c3po_root_node->get_sy(),c3po_root_node->get_sz());
	k+=3; c3po_node1->change_parameters(c3po_node1->get_tx(),c3po_node1->get_ty(),c3po_node1->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node1->get_sx(),c3po_node1->get_sy(),c3po_node1->get_sz());
	k+=3; c3po_node2->change_parameters(c3po_node2->get_tx(),c3po_node2->get_ty(),c3po_node2->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node2->get_sx(),c3po_node2->get_sy(),c3po_node2->get_sz());
	k+=3; c3po_node3->change_parameters(c3po_node3->get_tx(),c3po_node3->get_ty(),c3po_node3->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node3->get_sx(),c3po_node3->get_sy(),c3po_node3->get_sz());
	k+=3; c3po_node4->change_parameters(c3po_node4->get_tx(),c3po_node4->get_ty(),c3po_node4->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node4->get_sx(),c3po_node4->get_sy(),c3po_node4->get_sz());
	k+=3; c3po_node5->change_parameters(c3po_node5->get_tx(),c3po_node5->get_ty(),c3po_node5->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node5->get_sx(),c3po_node5->get_sy(),c3po_node5->get_sz());
	k+=3; c3po_node6->change_parameters(c3po_node6->get_tx(),c3po_node6->get_ty(),c3po_node6->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node6->get_sx(),c3po_node6->get_sy(),c3po_node6->get_sz());
	k+=3; c3po_node7->change_parameters(c3po_node7->get_tx(),c3po_node7->get_ty(),c3po_node7->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node7->get_sx(),c3po_node7->get_sy(),c3po_node7->get_sz());
	k+=3; c3po_node8->change_parameters(c3po_node8->get_tx(),c3po_node8->get_ty(),c3po_node8->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node8->get_sx(),c3po_node8->get_sy(),c3po_node8->get_sz());
	k+=3; c3po_node9->change_parameters(c3po_node9->get_tx(),c3po_node9->get_ty(),c3po_node9->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node9->get_sx(),c3po_node9->get_sy(),c3po_node9->get_sz());
	k+=3; c3po_node10->change_parameters(c3po_node10->get_tx(),c3po_node10->get_ty(),c3po_node10->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node10->get_sx(),c3po_node10->get_sy(),c3po_node10->get_sz());
	k+=3; c3po_node11->change_parameters(c3po_node11->get_tx(),c3po_node11->get_ty(),c3po_node11->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node11->get_sx(),c3po_node11->get_sy(),c3po_node11->get_sz());
	k+=3; c3po_node12->change_parameters(c3po_node12->get_tx(),c3po_node12->get_ty(),c3po_node12->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node12->get_sx(),c3po_node12->get_sy(),c3po_node12->get_sz());
	k+=3; c3po_node13->change_parameters(c3po_node13->get_tx(),c3po_node13->get_ty(),c3po_node13->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node13->get_sx(),c3po_node13->get_sy(),c3po_node13->get_sz());
	k+=3; c3po_node14->change_parameters(c3po_node14->get_tx(),c3po_node14->get_ty(),c3po_node14->get_tz(),interpolated_vals[k],interpolated_vals[k+1],interpolated_vals[k+2],c3po_node14->get_sx(),c3po_node14->get_sy(),c3po_node14->get_sz());
}

void initBuffersGL(void)
{
  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
  shader_light_flag1 = glGetUniformLocation(shaderProgram,"light_flag1");
  shader_light_flag2 = glGetUniformLocation(shaderProgram,"light_flag2");

  // Load Textures
  tex=LoadTexture("images/gold.bmp",600,300);
  glBindTexture(GL_TEXTURE_2D, tex);

  load("r2d2/r2d2_body", r2d2_body_positions,r2d2_body_colors, r2d2_body_normals, r2d2_body_tex_coords);
  load("r2d2/r2d2_head", r2d2_head_positions, r2d2_head_colors, r2d2_head_normals, r2d2_head_tex_coords);
  load("r2d2/r2d2_left_arm",r2d2_left_arm_positions,r2d2_left_arm_colors, r2d2_left_arm_normals, r2d2_left_arm_tex_coords);
  load("r2d2/r2d2_right_arm",r2d2_right_arm_positions,r2d2_right_arm_colors, r2d2_right_arm_normals, r2d2_right_arm_tex_coords);
  load("r2d2/r2d2_feet",r2d2_feet_positions,r2d2_feet_colors, r2d2_feet_normals, r2d2_feet_tex_coords);
  load("r2d2/r2d2_third_leg",r2d2_third_leg_positions,r2d2_third_leg_colors, r2d2_third_leg_normals, r2d2_third_leg_tex_coords);


  //note that the buffers are initialized in the respective constructors
  //body
  r2d2_node1 = new csX75::HNode(NULL,r2d2_body_positions.size(),&r2d2_body_positions[0],&r2d2_body_tex_coords[0],&r2d2_body_normals[0],r2d2_body_positions.size()*sizeof(glm::vec4),r2d2_body_tex_coords.size()*sizeof(glm::vec2),r2d2_body_normals.size()*sizeof(glm::vec4));
  r2d2_node1->change_parameters(-2.0,-3.0,0.0,0.0,0.0,0.0,0.3,0.3,0.3);
  //head
  r2d2_node2 = new csX75::HNode(r2d2_node1,r2d2_head_positions.size(),&r2d2_head_positions[0],&r2d2_head_tex_coords[0],&r2d2_head_normals[0],r2d2_head_positions.size()*sizeof(glm::vec4),r2d2_head_tex_coords.size()*sizeof(glm::vec2),r2d2_head_normals.size()*sizeof(glm::vec4));
  r2d2_node2->change_parameters(0.0,150.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);

  //right arm
  r2d2_node3 = new csX75::HNode(r2d2_node1,r2d2_right_arm_positions.size(),&r2d2_right_arm_positions[0],&r2d2_right_arm_tex_coords[0],&r2d2_right_arm_normals[0],r2d2_right_arm_positions.size()*sizeof(glm::vec4),r2d2_right_arm_tex_coords.size()*sizeof(glm::vec2),r2d2_right_arm_normals.size()*sizeof(glm::vec4));
  r2d2_node3->change_parameters(180.0/(512/14.0),90.0/(512/14.0),0.0,0.0,90.0,0.0,1.0,1.0,1.0);
  //left arm
  r2d2_node4 = new csX75::HNode(r2d2_node1,r2d2_left_arm_positions.size(),&r2d2_left_arm_positions[0],&r2d2_left_arm_tex_coords[0],&r2d2_left_arm_normals[0],r2d2_left_arm_positions.size()*sizeof(glm::vec4),r2d2_left_arm_tex_coords.size()*sizeof(glm::vec2),r2d2_left_arm_normals.size()*sizeof(glm::vec4));
  r2d2_node4->change_parameters(-180.0/(512/14.0),90.0/(512/14.0),0.0,0.0,-90.0,0.0,1.0,1.0,1.0);

  //right feet
  r2d2_node5 = new csX75::HNode(r2d2_node3,r2d2_feet_positions.size(),&r2d2_feet_positions[0],&r2d2_feet_tex_coords[0],&r2d2_feet_normals[0],r2d2_feet_positions.size()*sizeof(glm::vec4),r2d2_feet_tex_coords.size()*sizeof(glm::vec2),r2d2_feet_normals.size()*sizeof(glm::vec4));
  r2d2_node5->change_parameters(0.0/(512/14.0),-240.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left feet
  r2d2_node6 = new csX75::HNode(r2d2_node4,r2d2_feet_positions.size(),&r2d2_feet_positions[0],&r2d2_feet_tex_coords[0],&r2d2_feet_normals[0],r2d2_feet_positions.size()*sizeof(glm::vec4),r2d2_feet_tex_coords.size()*sizeof(glm::vec2),r2d2_feet_normals.size()*sizeof(glm::vec4));
  r2d2_node6->change_parameters(0.0/(512/14.0),-240.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);

  //third leg
  r2d2_node7 = new csX75::HNode(r2d2_node1,r2d2_third_leg_positions.size(),&r2d2_third_leg_positions[0],&r2d2_third_leg_tex_coords[0],&r2d2_third_leg_normals[0],r2d2_third_leg_positions.size()*sizeof(glm::vec4),r2d2_third_leg_tex_coords.size()*sizeof(glm::vec2),r2d2_third_leg_normals.size()*sizeof(glm::vec4));
  r2d2_node7->change_parameters(0.0,-150.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //third feet
  r2d2_node8 = new csX75::HNode(r2d2_node7,r2d2_feet_positions.size(),&r2d2_feet_positions[0],&r2d2_feet_tex_coords[0],&r2d2_feet_normals[0],r2d2_feet_positions.size()*sizeof(glm::vec4),r2d2_feet_tex_coords.size()*sizeof(glm::vec2),r2d2_feet_normals.size()*sizeof(glm::vec4));
  r2d2_node8->change_parameters(0.0,-30.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);

  r2d2_root_node = r2d2_node1;
  curr_root=r2d2_root_node;
  curr_node = r2d2_node1;

  load("c3po/c3po_body", c3po_body_positions,c3po_body_colors, c3po_body_normals, c3po_body_tex_coords);
  load("c3po/c3po_head", c3po_head_positions, c3po_head_colors, c3po_head_normals, c3po_head_tex_coords);
  load("c3po/c3po_upper_arm",c3po_upper_arm_positions,c3po_upper_arm_colors, c3po_upper_arm_normals, c3po_upper_arm_tex_coords);
  load("c3po/c3po_lower_arm",c3po_lower_arm_positions,c3po_lower_arm_colors, c3po_lower_arm_normals, c3po_lower_arm_tex_coords);
  load("c3po/c3po_upper_leg",c3po_upper_leg_positions,c3po_upper_leg_colors, c3po_upper_leg_normals, c3po_upper_leg_tex_coords);
  load("c3po/c3po_lower_leg",c3po_lower_leg_positions,c3po_lower_leg_colors, c3po_lower_leg_normals, c3po_lower_leg_tex_coords);
  load("c3po/c3po_wrist",c3po_wrist_positions,c3po_wrist_colors, c3po_wrist_normals, c3po_wrist_tex_coords);
  load("c3po/c3po_feet",c3po_feet_positions,c3po_feet_colors, c3po_feet_normals, c3po_feet_tex_coords);

  //body
  c3po_node1 = new csX75::HNode(NULL,c3po_body_positions.size(),&c3po_body_positions[0],&c3po_body_tex_coords[0],&c3po_body_normals[0],c3po_body_positions.size()*sizeof(glm::vec4),c3po_body_tex_coords.size()*sizeof(glm::vec2),c3po_body_normals.size()*sizeof(glm::vec4));
  c3po_node1->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //head
  c3po_node2 = new csX75::HNode(c3po_node1,c3po_head_positions.size(),&c3po_head_positions[0],&c3po_head_tex_coords[0],&c3po_head_normals[0],c3po_head_positions.size()*sizeof(glm::vec4),c3po_head_tex_coords.size()*sizeof(glm::vec2),c3po_head_normals.size()*sizeof(glm::vec4));
  c3po_node2->change_parameters(0.0,150.0/(512/14.0),0.0,0.0,0.0,0.0,0.9,1.0,1.0);

  //right upper arm
  c3po_node3 = new csX75::HNode(c3po_node1,c3po_upper_arm_positions.size(),&c3po_upper_arm_positions[0],&c3po_upper_arm_tex_coords[0],&c3po_upper_arm_normals[0],c3po_upper_arm_positions.size()*sizeof(glm::vec4),c3po_upper_arm_tex_coords.size()*sizeof(glm::vec2),c3po_upper_arm_normals.size()*sizeof(glm::vec4));
  c3po_node3->change_parameters(60.0/(512/14.0),150.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left upper arm
  c3po_node4 = new csX75::HNode(c3po_node1,c3po_upper_arm_positions.size(),&c3po_upper_arm_positions[0],&c3po_upper_arm_tex_coords[0],&c3po_upper_arm_normals[0],c3po_upper_arm_positions.size()*sizeof(glm::vec4),c3po_upper_arm_tex_coords.size()*sizeof(glm::vec2),c3po_upper_arm_normals.size()*sizeof(glm::vec4));
  c3po_node4->change_parameters(-60.0/(512/14.0),150.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //right lower arm
  c3po_node5 = new csX75::HNode(c3po_node3,c3po_lower_arm_positions.size(),&c3po_lower_arm_positions[0],&c3po_lower_arm_tex_coords[0],&c3po_lower_arm_normals[0],c3po_lower_arm_positions.size()*sizeof(glm::vec4),c3po_lower_arm_tex_coords.size()*sizeof(glm::vec2),c3po_lower_arm_normals.size()*sizeof(glm::vec4));
  c3po_node5->change_parameters(0.0/(512/14.0),-80.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left lower arm
  c3po_node6 = new csX75::HNode(c3po_node4,c3po_lower_arm_positions.size(),&c3po_lower_arm_positions[0],&c3po_lower_arm_tex_coords[0],&c3po_lower_arm_normals[0],c3po_lower_arm_positions.size()*sizeof(glm::vec4),c3po_lower_arm_tex_coords.size()*sizeof(glm::vec2),c3po_lower_arm_normals.size()*sizeof(glm::vec4));
  c3po_node6->change_parameters(0.0/(512/14.0),-80.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);

  //right wrist
  c3po_node7 = new csX75::HNode(c3po_node5,c3po_wrist_positions.size(),&c3po_wrist_positions[0],&c3po_wrist_tex_coords[0],&c3po_wrist_normals[0],c3po_wrist_positions.size()*sizeof(glm::vec4),c3po_wrist_tex_coords.size()*sizeof(glm::vec2),c3po_wrist_normals.size()*sizeof(glm::vec4));
  c3po_node7->change_parameters(0.0/(512/14.0),-80.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left wrist
  c3po_node8 = new csX75::HNode(c3po_node6,c3po_wrist_positions.size(),&c3po_wrist_positions[0],&c3po_wrist_tex_coords[0],&c3po_wrist_normals[0],c3po_wrist_positions.size()*sizeof(glm::vec4),c3po_wrist_tex_coords.size()*sizeof(glm::vec2),c3po_wrist_normals.size()*sizeof(glm::vec4));
  c3po_node8->change_parameters(0.0/(512/14.0),-80.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);

  //right upper leg
  c3po_node9 = new csX75::HNode(c3po_node1,c3po_upper_leg_positions.size(),&c3po_upper_leg_positions[0],&c3po_upper_leg_tex_coords[0],&c3po_upper_leg_normals[0],c3po_upper_leg_positions.size()*sizeof(glm::vec4),c3po_upper_leg_tex_coords.size()*sizeof(glm::vec2),c3po_upper_leg_normals.size()*sizeof(glm::vec4));
  c3po_node9->change_parameters(25.0/(512/14.0),0.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left upper leg
  c3po_node10 = new csX75::HNode(c3po_node1,c3po_upper_leg_positions.size(),&c3po_upper_leg_positions[0],&c3po_upper_leg_tex_coords[0],&c3po_upper_leg_normals[0],c3po_upper_leg_positions.size()*sizeof(glm::vec4),c3po_upper_leg_tex_coords.size()*sizeof(glm::vec2),c3po_upper_leg_normals.size()*sizeof(glm::vec4));
  c3po_node10->change_parameters(-25.0/(512/14.0),0.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //right lower leg
  c3po_node11 = new csX75::HNode(c3po_node9,c3po_lower_leg_positions.size(),&c3po_lower_leg_positions[0],&c3po_lower_leg_tex_coords[0],&c3po_lower_leg_normals[0],c3po_lower_leg_positions.size()*sizeof(glm::vec4),c3po_lower_leg_tex_coords.size()*sizeof(glm::vec2),c3po_lower_leg_normals.size()*sizeof(glm::vec4));
  c3po_node11->change_parameters(0.0/(512/14.0),-100.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left lower leg
  c3po_node12 = new csX75::HNode(c3po_node10,c3po_lower_leg_positions.size(),&c3po_lower_leg_positions[0],&c3po_lower_leg_tex_coords[0],&c3po_lower_leg_normals[0],c3po_lower_leg_positions.size()*sizeof(glm::vec4),c3po_lower_leg_tex_coords.size()*sizeof(glm::vec2),c3po_lower_leg_normals.size()*sizeof(glm::vec4));
  c3po_node12->change_parameters(0.0/(512/14.0),-100.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);

  //right feet
  c3po_node13 = new csX75::HNode(c3po_node11,c3po_feet_positions.size(),&c3po_feet_positions[0],&c3po_feet_tex_coords[0],&c3po_feet_normals[0],c3po_feet_positions.size()*sizeof(glm::vec4),c3po_feet_tex_coords.size()*sizeof(glm::vec2),c3po_feet_normals.size()*sizeof(glm::vec4));
  c3po_node13->change_parameters(0.0/(512/14.0),-100.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);
  //left feet
  c3po_node14 = new csX75::HNode(c3po_node12,c3po_feet_positions.size(),&c3po_feet_positions[0],&c3po_feet_tex_coords[0],&c3po_feet_normals[0],c3po_feet_positions.size()*sizeof(glm::vec4),c3po_feet_tex_coords.size()*sizeof(glm::vec2),c3po_feet_normals.size()*sizeof(glm::vec4));
  c3po_node14->change_parameters(0.0/(512/14.0),-100.0/(512/14.0),0.0,0.0,0.0,0.0,1.0,1.0,1.0);


  c3po_root_node = c3po_node1;
  // root_node = curr_node = c3po_node1;



}

void renderGL(void)
{

  if(playback){
  	double t = glfwGetTime();
  	int frame_number = floor(t*FPS);
  	int interpolation_num = frame_number%num_interpolations;
  	int keyframe_number = frame_number/num_interpolations;
  	if(keyframe_number +1 >= keyframes.size()){
  		playback = false;
  		std::cout<<"playback ended successfully."<<std::endl;
  	}
  	else{
  		set_parameters(keyframe_number,interpolation_num);
      capture_frame(frame_number);
  	}
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    //projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 100.0);
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,100.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -7.0, 7.0);

  view_matrix = projection_matrix*lookat_matrix;
  //view_matrix = projection_matrix;
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glUniform1i(shader_light_flag1,light_flag1);
  glUniform1i(shader_light_flag2,light_flag2);


  //matrixStack.push_back(view_matrix);

  r2d2_root_node->render_tree();
  c3po_root_node->render_tree();
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
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

//-------------------------------------------------------------------------

