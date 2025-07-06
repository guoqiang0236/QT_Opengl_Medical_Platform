#version 450 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;

uniform sampler2D sampler;
//��Դ����
uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
  // 1 ��ȡ���嵱ǰ���ص���ɫ
  vec3 objectColor = texture(sampler, uv).xyz;

  // 2 ׼��diffuse(������)�������

  // ����ֵ��ķ��߹�һ����ȷ���䳤��Ϊ1��������ռ������
  vec3 normalizedNormal = normalize(normal);

  // ����Դ�����һ����ȷ���䳤��Ϊ1
  vec3 lightDirN = normalize(lightDirection);
  
  // ���������������
  // dot(-lightDirN, normalizedNormal) ��ʾ�������䷽������淨�ߵļн�����
  // ȡ��������ΪlightDirectionͨ��Ϊ�����ߴӹ�Դָ�����塱�ķ���
  // ����������Ҫ��������ָ���Դ���ķ���
  float diffuse = clamp(dot(-lightDirN, normalizedNormal),0.0,1.0);
  
  // ����������ɫ����Դ��ɫ * ������ϵ�� * ���屾����ɫ
  vec3 finalColor = lightColor * diffuse * objectColor;

  FragColor =vec4(finalColor, 1.0);


  
}