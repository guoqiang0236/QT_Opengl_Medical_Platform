#pragma once

#include "../../pch.h"

// ʹ��C++��ö������
enum class MaterialType {
    PhongMaterial
};

class MyMaterial :public QObject {
    Q_OBJECT
public:
    MyMaterial();
    ~MyMaterial();
public:
    MaterialType mType;
};