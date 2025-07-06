#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal;

uniform mat4 transform;
uniform mat4 viewMatrix; //��ͼ����
uniform mat4 projectionMatrix; //ͶӰ����

//aPos��Ϊattribute�����ԣ�����shader
//��������ĵ�
void main()
{
    vec4 position =vec4(aPos, 1.0);
    position = projectionMatrix * viewMatrix * transform * position;
    gl_Position = position;
    uv = aUV;
    normal= aNormal;
}
