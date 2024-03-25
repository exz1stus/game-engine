#version 410 core
out vec4 color;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
};

uniform sampler2D u_Textures[32];

layout (location = 0) in VertexOutput Input;

void main()
{
	//glsl float precision +0.5
	int texIndex = int(floor(Input.TexIndex + 0.5));
	
	color = Input.Color * texture(u_Textures[texIndex], Input.TexCoord * Input.TilingFactor);
}
