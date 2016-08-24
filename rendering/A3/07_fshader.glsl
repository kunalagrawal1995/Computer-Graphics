#version 330

in vec3 normal;
in vec4 eye;
out vec4 frag_color;

uniform mat4 viewMatrix;
uniform sampler2D texture;
varying vec2 tex;

uniform int light_flag1, light_flag2;

void main (void) 
{
    vec4 COLOR = texture2D(texture, tex);	
    //frag_color = color;	

    // Defining Materials
  vec4 diffuse = vec4(0.5, 0.4, 0.0, 1.0); 
  vec4 ambient = vec4(0.1, 0.0, 0.0, 1.0);
  vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
  float shininess = 10.0;
  vec4 spec = vec4(0.0);
  vec4 spec2 = vec4(0.0); 

  // Defining Light 1
  vec4 lightPos = vec4(3.0, 3.0, 3.0, 0.0);
  vec3 lightDir = vec3(viewMatrix * lightPos);  // Transforms with camera
  lightDir = normalize( vec3(lightDir)); 

  // Defining Light 2
  vec4 lightPos2 = vec4(-3.0, -3.0, -3.0, 0.0);
  vec3 lightDir2 = vec3(viewMatrix * lightPos2);  // Transforms with camera
  lightDir2 = normalize( vec3(lightDir2));  

  //Diffuse for light 1
  vec3 n = normalize(vec3(normal));	     
  float dotProduct = dot(n, lightDir);
  float intensity =  max( dotProduct, 0.0);

  //Diffuse for light 2
  float dotProduct2 = dot(n, lightDir2);
  float intensity2 =  max( dotProduct2, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	vec3 e = normalize(vec3(eye));
	vec3 h = normalize(lightDir + e );
   	float intSpec = max(dot(h,n), 0.0);	
    spec = specular * pow(intSpec, shininess);
  }

  // if(dotProduct >= 0.0){
  // 	intensity = 10.0;
  // }

  // Compute specular component only if light falls on vertex
  if(intensity2 > 0.0)
  {
	vec3 e = normalize(vec3(eye));
	vec3 h = normalize(lightDir2 + e );
   	float intSpec = max(dot(h,n), 0.0);
   	spec2 = specular * pow(intSpec, shininess);
  }
  vec4 color,color1;
  if(light_flag1==1)
  	color = max((intensity * diffuse  + spec)*COLOR, ambient);
  else
  	color = ambient;
  if(light_flag2==1)
  	color1 = max((intensity2 * diffuse  + spec2)*COLOR, ambient);
  else
  	color1 = ambient;
  // color = ambient;
  // color += ambient;
  frag_color = color + color1;
  // frag_color = COLOR_DUMMY;
}
