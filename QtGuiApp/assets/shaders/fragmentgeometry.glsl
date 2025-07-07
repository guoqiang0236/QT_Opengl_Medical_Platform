#version 450 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform sampler2D sampler;
//��Դ����
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float specularIntensity; //���淴��ǿ��
uniform vec3 ambientColor; //��������ɫ

//���������λ��
uniform vec3 cameraPosition;


void main()
{
  // 1 ������յ�ͨ������
  vec3 objectColor = texture(sampler, uv).xyz;
  vec3 normalizedNormal = normalize(normal); // ����ֵ��ķ��߹�һ����ȷ���䳤��Ϊ1��������ռ������
  vec3 lightDirN = normalize(lightDirection); // ����Դ�����һ����ȷ���䳤��Ϊ1
  vec3 viewDir = normalize(worldPosition - cameraPosition); // ���߷���

  // 2 ����diffuse(������)�������
  float diffuse = clamp(dot(-lightDirN, normalizedNormal),0.0,1.0);  // ��������������� dot(-lightDirN, normalizedNormal) ��ʾ�������䷽������淨�ߵļн�����
  vec3 diffuseColor = lightColor * diffuse * objectColor; // ����������ɫ����Դ��ɫ * ������ϵ�� * ���屾����ɫ

  // 3 ����specular (���淴��)�������
  float doResult = dot(-lightDirN, normalizedNormal);// ��ֹ�����Ч��
  float flag = step(0.0, doResult); // ���doResultС��0����flagΪ0������Ϊ1
  vec3 lightReflect = normalize(reflect(lightDirN, normalizedNormal)); // ������߷��䷽��
  float specular = clamp(dot(lightReflect, -viewDir), 0.0, 1.0); // ���㾵�淴�����
  specular = pow(specular, 32.0); // ���ƹ�ߴ�С��32.0��һ�����õ�ֵ�����Ը�����Ҫ����
  vec3 specularColor = lightColor * specular * flag * specularIntensity;

  // 4 ���㻷����
  vec3 ambientColorFinal = ambientColor * objectColor; // ��������ɫ��������ɫ�ĳ˻�


  vec3 finalColor = diffuseColor + specularColor + ambientColorFinal; // ������ɫΪ������;��淴��ͻ�����ĺ�

  FragColor = vec4(finalColor, 1.0); // �����߷�������ɫ���

  
}