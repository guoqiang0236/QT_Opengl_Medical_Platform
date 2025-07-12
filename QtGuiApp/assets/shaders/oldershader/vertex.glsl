#version 450 core
layout (location = 3) in vec3 aPos;
layout (location = 4) in vec3 aColor;
layout (location = 5) in vec2 aUV;

out vec3 color;
out vec2 uv;
uniform float time;

void main()
{
	//1 ��ǰ�����εĶ��㣬���ŵı���
	float scale  = 1.0 / time;
	
	//2 ʹ��scale�Զ���λ�ý�������
	vec3 sPos = aPos * scale;

	//3 �����λ����Ϣ
	gl_Position= vec4(sPos, 1.0);
	color = aColor;
	uv = aUV;
}