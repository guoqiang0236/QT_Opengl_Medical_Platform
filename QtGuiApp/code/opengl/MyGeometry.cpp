#include "MyGeometry.h"

MyGeometry::MyGeometry(QObject* parent)
{
    initializeOpenGLFunctions();
}

MyGeometry::~MyGeometry()
{
	if (mVao != 0)
	{
		glDeleteVertexArrays(1, &mVao);
		mVao = 0;
	}
	if (mPosVbo != 0)
	{
		glDeleteBuffers(1, &mPosVbo);
		mPosVbo = 0;
	}
	if (mUvVao != 0)
	{
		glDeleteBuffers(1, &mUvVao);
		mUvVao = 0;
	}
	if (mEbo != 0)
	{
		glDeleteBuffers(1, &mEbo);
		mEbo = 0;
	}
}

MyGeometry* MyGeometry::createBox(float size)
{
	MyGeometry* geometry = new MyGeometry();
    // �����嶥�����ݣ��߳� = 2 * halfSize��
    const float halfSize = 0.5f; // �������߳�

	geometry->mIndicesCount = 36; // ��������6���棬ÿ����2�������Σ�ÿ��������3�����㣬�ܹ�6*2*3=36������

    // ����λ������ (24�����㣬ÿ����4������)
    float positions[] = {
        // ǰ�� (Front)
        -halfSize, -halfSize,  halfSize, // ����
         halfSize, -halfSize,  halfSize, // ����
         halfSize,  halfSize,  halfSize, // ����
        -halfSize,  halfSize,  halfSize, // ����

        // ���� (Back)
         halfSize, -halfSize, -halfSize, // ����
        -halfSize, -halfSize, -halfSize, // ����
        -halfSize,  halfSize, -halfSize, // ����
         halfSize,  halfSize, -halfSize, // ����

         // ���� (Left)
         -halfSize, -halfSize, -halfSize, // ����
         -halfSize, -halfSize,  halfSize, // ����
         -halfSize,  halfSize,  halfSize, // ����
         -halfSize,  halfSize, -halfSize, // ����

         // ���� (Right)
          halfSize, -halfSize,  halfSize, // ����
          halfSize, -halfSize, -halfSize, // ����
          halfSize,  halfSize, -halfSize, // ����
          halfSize,  halfSize,  halfSize, // ����

          // ���� (Top)
          -halfSize,  halfSize,  halfSize, // ����
           halfSize,  halfSize,  halfSize, // ����
           halfSize,  halfSize, -halfSize, // ����
          -halfSize,  halfSize, -halfSize, // ����

          // ���� (Bottom)
          -halfSize, -halfSize, -halfSize, // ����
           halfSize, -halfSize, -halfSize, // ����
           halfSize, -halfSize,  halfSize, // ����
          -halfSize, -halfSize,  halfSize  // ����
    };

    // UV�������� (ÿ����4��UV����)
    float uvs[] = {
        // ÿ�����UV����˳��: ����(0,0), ����(1,0), ����(1,1), ����(0,1)
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f, // Front
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f, // Back
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f, // Left
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f, // Right
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f, // Top
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f  // Bottom
    };

    // �������� (36��������ÿ����6������)
    unsigned int indices[] = {
        // ǰ��
        0, 1, 2,  2, 3, 0,
        // ����
        4, 5, 6,  6, 7, 4,
        // ����
        8, 9, 10,  10, 11, 8,
        // ����
        12, 13, 14,  14, 15, 12,
        // ����
        16, 17, 18,  18, 19, 16,
        // ����
        20, 21, 22,  22, 23, 20
    };
	
    // VBO����
	GLuint& posVbo = geometry->mPosVbo, uvVbo = geometry->mUvVao, ebo = geometry->mEbo;
    //POS
    geometry->glGenBuffers(1, &posVbo);
	geometry->glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	geometry->glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    //UV
	geometry->glGenBuffers(1, &uvVbo);
	geometry->glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	geometry->glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	//EBO
	geometry->glGenBuffers(1, &ebo);
	geometry->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	geometry->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
    // VAO����
	geometry->glGenVertexArrays(1, &geometry->mVao);
	geometry->glBindVertexArray(geometry->mVao);

	// �󶨶���λ��
	geometry->glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    geometry->glEnableVertexAttribArray(0);
    geometry->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// ��UV����
	geometry->glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	geometry->glEnableVertexAttribArray(1);
	geometry->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// ��EBO
	geometry->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    geometry->glBindVertexArray(0);
	return geometry;
}

MyGeometry* MyGeometry::createSphere(float size)
{
	MyGeometry* geometry = new MyGeometry();

	return geometry;
}
