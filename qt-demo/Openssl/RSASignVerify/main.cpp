#include <QCoreApplication>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    // 读取
    return a.exec();
}

char* rsa_sign(char* c_sHash, int nHashLen, char* c_szKeypath)
{
    return nullptr;
}
