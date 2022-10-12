#shader vertex
#version 430 core  

layout(location = 0) in vec3 position;
// Instancing Transformations
layout(location = 1) in mat4 transform;



uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
   
void main()
{
	gl_Position = proj * view * transform * vec4(position, 1.0f);
};

#shader fragment
#version 430 core  
   
layout(location = 0) out vec4 color;   /*Important LOC bcs of the change to  out  in the vector type specifier*/


/*Declaring an uniform.Uniform is a way of transporting data from CPU to the GPU.That makes me able to change the shader parameters
on the fly from the source code.*/

uniform vec4 u_Color;
uniform sampler2D u_Texture;
   
void main()
{
	color = u_Color;
};