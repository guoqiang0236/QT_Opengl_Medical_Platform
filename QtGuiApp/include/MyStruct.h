#include <QMetaType>
#include <QString>

struct MyStruct
{
    int id;
    QString name;
};

Q_DECLARE_METATYPE(MyStruct) // ����ΪԪ����

// �ڳ����ʼ���׶�ע��
void registerMyStructMetaType()
{
    qRegisterMetaType<MyStruct>("MyStruct");
}
