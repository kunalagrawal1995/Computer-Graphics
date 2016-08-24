#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz,sx,sy,sz;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;
		std::size_t tex_buffer_size;
		std::size_t normal_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
		glm::mat4 scaling;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  public:
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec2*, glm::vec4*, std::size_t, std::size_t, std::size_t);
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void render_tree();
		void inc_tx();
		void inc_ty();
		void inc_tz();
		void dec_tx();
		void dec_ty();
		void dec_tz();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void inc_sx();
		void inc_sy();
		void inc_sz();
		void dec_sx();
		void dec_sy();
		void dec_sz();
		GLfloat get_tx();
		GLfloat get_ty();
		GLfloat get_tz();
		GLfloat get_rx();
		GLfloat get_ry();
		GLfloat get_rz();
		GLfloat get_sx();
		GLfloat get_sy();
		GLfloat get_sz();
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif