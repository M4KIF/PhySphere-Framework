#shader vertex
#version 460 core  
   
layout(location = 0) in vec3 m_Position; 
layout(location = 1) in vec3 m_Color;
layout(location = 2) in vec3 m_Normal;

out vec3 o_Color;

uniform mat4 mvp;
   
void main()
{
	gl_Position = mvp * vec4(m_Position, 1.0f);
	o_Color = normalize(vec3(m_Color));
	//o_Color = normalize(vec4(0.5f, 0.2f, 0.3f, 1.0f));
};

#shader fragment
#version 460 core


in vec3 o_Color;
layout(location = 0) out vec4 Color;
   
void main()
{
	Color = vec4(o_Color, 1.0f);
};