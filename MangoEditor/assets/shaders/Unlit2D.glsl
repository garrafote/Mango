// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;
layout(location = 4) in vec4 a_Tiling;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out int v_TexIndex;
out vec4 v_Tiling;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_Tiling = a_Tiling;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out int id;

in vec4 v_Color;
in vec2 v_TexCoord;
flat in int v_TexIndex;
in vec4 v_Tiling;

uniform sampler2D u_Textures[32];

vec4 texture_32(in sampler2D textures[32], in int index, in vec2 texCoord)
{
	switch(index)
	{
		case 0:   return texture(u_Textures[0],  texCoord);
		case 1:   return texture(u_Textures[1],  texCoord);
		case 2:   return texture(u_Textures[2],  texCoord);
		case 3:   return texture(u_Textures[3],  texCoord);
		case 4:   return texture(u_Textures[4],  texCoord);
		case 5:   return texture(u_Textures[5],  texCoord);
		case 6:   return texture(u_Textures[6],  texCoord);
		case 7:   return texture(u_Textures[7],  texCoord);
		case 8:   return texture(u_Textures[8],  texCoord);
		case 9:   return texture(u_Textures[9],  texCoord);
		case 10:  return texture(u_Textures[10], texCoord);
		case 11:  return texture(u_Textures[11], texCoord);
		case 12:  return texture(u_Textures[12], texCoord);
		case 13:  return texture(u_Textures[13], texCoord);
		case 14:  return texture(u_Textures[14], texCoord);
		case 15:  return texture(u_Textures[15], texCoord);
		case 16:  return texture(u_Textures[16], texCoord);
		case 17:  return texture(u_Textures[17], texCoord);
		case 18:  return texture(u_Textures[18], texCoord);
		case 19:  return texture(u_Textures[19], texCoord);
		case 20:  return texture(u_Textures[20], texCoord);
		case 21:  return texture(u_Textures[21], texCoord);
		case 22:  return texture(u_Textures[22], texCoord);
		case 23:  return texture(u_Textures[23], texCoord);
		case 24:  return texture(u_Textures[24], texCoord);
		case 25:  return texture(u_Textures[25], texCoord);
		case 26:  return texture(u_Textures[26], texCoord);
		case 27:  return texture(u_Textures[27], texCoord);
		case 28:  return texture(u_Textures[28], texCoord);
		case 29:  return texture(u_Textures[29], texCoord);
		case 30:  return texture(u_Textures[30], texCoord);
		case 31:  return texture(u_Textures[31], texCoord);
	}
}

void main()
{
	//color = texture_32(u_Textures, v_TexIndex, v_TexCoord * v_Tiling.xy + v_Tiling.zw) * v_Color;
	color = texture(u_Textures[v_TexIndex], v_TexCoord * v_Tiling.xy + v_Tiling.zw) * v_Color;
	id = 50;
}
