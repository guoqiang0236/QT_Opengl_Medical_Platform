#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix; //��ͼ����
uniform mat4 projectionMatrix; //ͶӰ����





void main()
{

    // ������Ķ���λ�ã�ת��Ϊ�������(3ά->4ά)
    vec4 transformPosition = vec4(aPos, 1.0);

    // ��һ���м����transformPosition�����ڼ�����λλ����modelMatrix��˵��м���
    transformPosition = modelMatrix * transformPosition;


    // ��������λ�ã�����ͶӰ����ͼ�任��
    gl_Position = projectionMatrix * viewMatrix * transformPosition;

 

    // ������������
    uv = aUV;
    normal=aNormal;
}
