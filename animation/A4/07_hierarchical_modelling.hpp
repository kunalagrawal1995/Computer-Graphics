/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 6.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;

//light controls
GLint light_flag1 = 1;
GLint light_flag2 = 1;
//Shader program attribs
GLuint vPosition,vColor,vNormal,texCoord,shaderProgram,uModelViewMatrix,viewMatrix,normalMatrix,tex;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

//r2d2 positions, colors and normals
std::vector<glm::vec4> r2d2_head_positions;
std::vector<glm::vec4> r2d2_head_colors;
std::vector<glm::vec4> r2d2_head_normals;
std::vector<glm::vec2> r2d2_head_tex_coords;

std::vector<glm::vec4> r2d2_body_positions;
std::vector<glm::vec4> r2d2_body_colors;
std::vector<glm::vec4> r2d2_body_normals;
std::vector<glm::vec2> r2d2_body_tex_coords;

std::vector<glm::vec4> r2d2_left_arm_positions;
std::vector<glm::vec4> r2d2_left_arm_colors;
std::vector<glm::vec4> r2d2_left_arm_normals;
std::vector<glm::vec2> r2d2_left_arm_tex_coords;

std::vector<glm::vec4> r2d2_right_arm_positions;
std::vector<glm::vec4> r2d2_right_arm_colors;
std::vector<glm::vec4> r2d2_right_arm_normals;
std::vector<glm::vec2> r2d2_right_arm_tex_coords;

std::vector<glm::vec4> r2d2_feet_positions;
std::vector<glm::vec4> r2d2_feet_colors;
std::vector<glm::vec4> r2d2_feet_normals;
std::vector<glm::vec2> r2d2_feet_tex_coords;

std::vector<glm::vec4> r2d2_third_leg_positions;
std::vector<glm::vec4> r2d2_third_leg_colors;
std::vector<glm::vec4> r2d2_third_leg_normals;
std::vector<glm::vec2> r2d2_third_leg_tex_coords;


csX75::HNode* r2d2_root_node;
csX75::HNode* c3po_root_node;
csX75::HNode* curr_root;
csX75::HNode* curr_node;

csX75::HNode* r2d2_node1;	//body
csX75::HNode* r2d2_node2;	//head
csX75::HNode* r2d2_node3;	//right arm
csX75::HNode* r2d2_node4;	//left arm
csX75::HNode* r2d2_node5;	//right feet
csX75::HNode* r2d2_node6;	//left feet
csX75::HNode* r2d2_node7;	//third leg
csX75::HNode* r2d2_node8;	//third feet

//r2d2 positions, colors and normals
std::vector<glm::vec4> c3po_head_positions;
std::vector<glm::vec4> c3po_head_colors;
std::vector<glm::vec4> c3po_head_normals;
std::vector<glm::vec2> c3po_head_tex_coords;

std::vector<glm::vec4> c3po_body_positions;
std::vector<glm::vec4> c3po_body_colors;
std::vector<glm::vec4> c3po_body_normals;
std::vector<glm::vec2> c3po_body_tex_coords;

std::vector<glm::vec4> c3po_upper_arm_positions;
std::vector<glm::vec4> c3po_upper_arm_colors;
std::vector<glm::vec4> c3po_upper_arm_normals;
std::vector<glm::vec2> c3po_upper_arm_tex_coords;

std::vector<glm::vec4> c3po_lower_arm_positions;
std::vector<glm::vec4> c3po_lower_arm_colors;
std::vector<glm::vec4> c3po_lower_arm_normals;
std::vector<glm::vec2> c3po_lower_arm_tex_coords;

std::vector<glm::vec4> c3po_upper_leg_positions;
std::vector<glm::vec4> c3po_upper_leg_colors;
std::vector<glm::vec4> c3po_upper_leg_normals;
std::vector<glm::vec2> c3po_upper_leg_tex_coords;

std::vector<glm::vec4> c3po_lower_leg_positions;
std::vector<glm::vec4> c3po_lower_leg_colors;
std::vector<glm::vec4> c3po_lower_leg_normals;
std::vector<glm::vec2> c3po_lower_leg_tex_coords;

std::vector<glm::vec4> c3po_wrist_positions;
std::vector<glm::vec4> c3po_wrist_colors;
std::vector<glm::vec4> c3po_wrist_normals;
std::vector<glm::vec2> c3po_wrist_tex_coords;

std::vector<glm::vec4> c3po_feet_positions;
std::vector<glm::vec4> c3po_feet_colors;
std::vector<glm::vec4> c3po_feet_normals;
std::vector<glm::vec2> c3po_feet_tex_coords;

csX75::HNode* c3po_node1;	//body
csX75::HNode* c3po_node2;	//head
csX75::HNode* c3po_node3;	//right upper arm
csX75::HNode* c3po_node4;	//left upper arm
csX75::HNode* c3po_node5;	//right lower arm
csX75::HNode* c3po_node6;	//left lower arm
csX75::HNode* c3po_node7;	//right wrist
csX75::HNode* c3po_node8;	//left wrist
csX75::HNode* c3po_node9;	//right uppper leg
csX75::HNode* c3po_node10;	//left upper leg
csX75::HNode* c3po_node11;	//right lower leg
csX75::HNode* c3po_node12;	//left lower leg
csX75::HNode* c3po_node13;	//right feet
csX75::HNode* c3po_node14;	//left feet

bool playback=false;
int FPS=30;
int num_interpolations=10;

std::vector < std::vector<GLfloat> > keyframes;


//-------------------------------------------------------------------------

#endif
