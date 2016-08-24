#include "hierarchy_node.hpp"
#include <iostream>

extern GLuint vPosition,vColor,uModelViewMatrix,texCoord,vNormal,normalMatrix,shaderProgram;
extern std::vector<glm::mat4> matrixStack;
extern glm::mat4 view_matrix;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec2* a_tex, glm::vec4* a_normals, std::size_t v_size, std::size_t t_size, std::size_t n_size){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		// color_buffer_size = c_size;
		tex_buffer_size = t_size;
		normal_buffer_size = n_size;
		// initialize vao and vbo of the object;
		// tex=LoadTexture(path,256,256);
  // 		glBindTexture(GL_TEXTURE_2D, tex);

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + tex_buffer_size + normal_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, tex_buffer_size, a_tex );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + tex_buffer_size, normal_buffer_size, a_normals );

		//setup the vertex array as per the shader
		vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
		glEnableVertexAttribArray( texCoord );
		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + tex_buffer_size));


		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;
		sx=sy=sz=1.0;

		update_matrices();
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		scaling = glm::scale(glm::mat4(1.0f), glm::vec3(sx,sy,sz));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz, GLfloat asx, GLfloat asy, GLfloat asz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;
		sx = asx;
		sy = asy;
		sz = asz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);
		uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix * (*ms_mult)));

		glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
		normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		//matrixStack.push_back(scaling);
		matrixStack.push_back(rotation);
		matrixStack.push_back(scaling);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	GLfloat HNode::get_tx(){
		return tx;
	}

	GLfloat HNode::get_ty(){
		return ty;
	}

	GLfloat HNode::get_tz(){
		return tz;
	}

	GLfloat HNode::get_rx(){
		return rx;
	}

	GLfloat HNode::get_ry(){
		return ry;
	}

	GLfloat HNode::get_rz(){
		return rz;
	}

	GLfloat HNode::get_sx(){
		return sx;
	}

	GLfloat HNode::get_sy(){
		return sy;
	}

	GLfloat HNode::get_sz(){
		return sz;
	}

	void HNode::inc_tx(){
		tx+=0.1;
		update_matrices();
	}


	void HNode::inc_ty(){
		ty+=0.1;
		update_matrices();
	}

	void HNode::inc_tz(){
		tz+=0.1;
		update_matrices();
	}

	void HNode::dec_tx(){
		tx-=0.1;
		update_matrices();
	}

	void HNode::dec_ty(){
		ty-=0.1;
		update_matrices();
	}

	void HNode::dec_tz(){
		tz-=0.1;
		update_matrices();
	}

	void HNode::inc_rx(){
		rx+=30.0;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry+=30.0;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz+=30.0;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx-=30.0;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry-=30.0;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz-=30.0;
		update_matrices();
	}

	void HNode::inc_sx(){
		sx++;
		update_matrices();
	}


	void HNode::inc_sy(){
		sy++;
		update_matrices();
	}

	void HNode::inc_sz(){
		sz++;
		update_matrices();
	}

	void HNode::dec_sx(){
		sx--;
		update_matrices();
	}

	void HNode::dec_sy(){
		sy--;
		update_matrices();
	}

	void HNode::dec_sz(){
		sz--;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}