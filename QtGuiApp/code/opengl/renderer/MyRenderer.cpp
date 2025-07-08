#include "MyRenderer.h"

MyRenderer::MyRenderer()
{
	initializeOpenGLFunctions();
	mPhongShader = new MyShader("../assets/shaders/phong.vert", "../assets/shaders/phong.frag");
}

MyRenderer::~MyRenderer()
{
	if (mPhongShader)
	{
		delete mPhongShader;
		mPhongShader = nullptr;
	}
}

void MyRenderer::render(const std::vector<MyMesh*>& meshes, MyCamera* camera, MyDirectionalLight* dirLight, MyAmbientLight* ambLight)
{
	//1 ���õ�ǰ֡���Ƶ�ʱ��,opengl�ı�Ҫ״̬������
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//2 ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//3 ����mesh��Ⱦ
    for (int i = 0; i < meshes.size(); i++) {
        auto mesh = meshes[i];
        auto geometry = mesh->mGeometry;
        auto material = mesh->mMaterial;

        // 1. ����ʹ���ĸ�Shader
		MyShader* shader = pickShader(material->mType);


        // 2. ����shader��uniform
		shader->begin();

		switch (material->mType) {
		case MaterialType::PhongMaterial: {
			MyPhongMaterial* phongMat = static_cast<MyPhongMaterial*>(material);

			//diffuse��ͼ
		    //�����������������Ԫ�ҹ�
			shader->setInt("sampler", 0);
			//������������Ԫ���йҹ�
			phongMat->mDiffuse->bind();

			//mvp����ĸ���
			shader->setMatrix4x4("modelMatrix", mesh->getModelMatrix());
			shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
			shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());

			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(mesh->getModelMatrix())));
			shader->setMatrix3x3("normalMatrix", normalMatrix);

			// ��Դ������uniform����
			shader->setVector3("lightDirection", dirLight->mDirection);
			shader->setVector3("lightColor", dirLight->mColor);
			shader->setFloat("specularIntensity", dirLight->mSpecularIntensity);
			shader->setVector3("ambientColor", ambLight->mColor);

			//�����Ϣ����
			shader->setVector3("cameraPosition", camera->mPosition);
			break;
		}
		default:
			continue;
		}
		
        // 3. ��vao
		glBindVertexArray(geometry->getVao());

        // 4. ִ�л�������
		glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, (void*)(sizeof(int) * 0));
		
    }
}

MyShader* MyRenderer::pickShader(MaterialType type)
{
	MyShader* result = nullptr;
	switch (type)
	{
	case MaterialType::PhongMaterial:
		result = mPhongShader;
		break;
	//case MaterialType::WhiteMaterial:
	//	result = mWhiteShader;
	//	break;
	//case MaterialType::DepthMaterial:
	//	result = mDepthShader;
	//	break;
	//case MaterialType::OpacityMaskMaterial:
	//	result = mOpacityMaskShader;
	//	break;
	//case MaterialType::ScreenMaterial:
	//	result = mScreenShader;
	//	break;
	//case MaterialType::CubeMaterial:
	//	result = mCubeShader;
	//	break;
	//case MaterialType::PhongEnvMaterial:
	//	result = mPhongEnvShader;
	//	break;
	//case MaterialType::PhongInstanceMaterial:
	//	result = mPhongInstancedShader;
	//	break;
	//case MaterialType::GrassInstanceMaterial:
	//	result = mGrassInstanceShader;
	//	break;
	default:
		std::cout << "Unknown material type to pick shader" << std::endl;
		break;
	}
	return result;
}


