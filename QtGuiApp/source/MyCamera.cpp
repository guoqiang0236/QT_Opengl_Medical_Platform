#include "MyCamera.h"

MyCamera::MyCamera()
{
}

MyCamera::~MyCamera()
{
}

glm::mat4 MyCamera::getViewMatrix()
{
    // lookAt
    // - eye:    ���λ�ã�ʹ�� mPosition��
    // - center: ��������������ĸ���
    // - top:    񷶥��ʹ�� mUp �����
	glm::vec3 front = glm::cross(mUp, mRight);
	glm::vec3 center = mPosition + front;

	return glm::lookAt(mPosition, center, mUp);
}
