#include "MyCamera.h"

MyCamera::MyCamera(QObject* parent)
{
}

MyCamera::~MyCamera()
{
}

glm::mat4 MyCamera::getProjectionMatrix()
{
  
	//������෵�ص�λ����
	return glm::identity<glm::mat4>();
}
