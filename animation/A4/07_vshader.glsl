#version 330

in vec4 vPosition;
uniform mat4 uModelViewMatrix;

in vec2 texCoord;
in vec3 vNormal;
varying vec2 tex;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

out vec3 normal;
out vec4 eye;
void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = - (uModelViewMatrix * gl_Position);
  tex = texCoord;
}
