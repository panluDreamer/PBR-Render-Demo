#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_tangent;
layout (location = 3) in vec2 in_uv;
out vec3 world_pos;
out vec2 uv;
out vec3 normal;
out vec3 tangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 ModelInverseTranspose;
void main()
{
	gl_Position = projection * view * model * vec4(in_pos, 1.0f);
	uv = in_uv;
	world_pos = vec3(model*vec4(in_pos,1.0f));//inverse-transpose?
	normal = mat3(ModelInverseTranspose) * in_normal;
	tangent = mat3(ModelInverseTranspose) * in_tangent;
}