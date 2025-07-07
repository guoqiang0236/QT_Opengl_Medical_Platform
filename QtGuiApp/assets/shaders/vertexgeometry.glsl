#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal;
out vec3 worldPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix; //��ͼ����
uniform mat4 projectionMatrix; //ͶӰ����



//aPos��Ϊattribute�����ԣ�����shader
//��������ĵ�
void main()
{
    //vec4 position =vec4(aPos, 1.0);

    // ������Ķ���λ�ã�ת��Ϊ�������(3ά->4ά)
    vec4 transformPosition = vec4(aPos, 1.0);

    // ��һ���м����transformPosition�����ڼ�����λλ����modelMatrix��˵��м���
    transformPosition = modelMatrix * transformPosition;

    // ���㵱ǰ�����worldPosition������������FragmentShader
    worldPosition = transformPosition.xyz;

    // ��������λ�ã�����ͶӰ����ͼ�任��
    vec4 position = projectionMatrix * viewMatrix * transformPosition;
    gl_Position = position;
 

    // ������������
    uv = aUV;
    normal= aNormal;
}
