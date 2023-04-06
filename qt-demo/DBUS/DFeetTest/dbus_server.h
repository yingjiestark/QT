#ifndef DBUS_SERVER_H
#define DBUS_SERVER_H

#include <QObject>
#include <QtDebug>
#include <QtDBus/QDBusConnection>
#include <QDBusVariant>
#define DBUS_NAME "com.dfeet.test"
#define DBUS_PATH "/test"

struct Persion {
    QString Name;
    int age;
};
Q_DECLARE_METATYPE(Persion)
class DBUSServer : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.dbus.test")
   public:
    explicit DBUSServer(QObject *parent = nullptr);

   signals:

   public slots:
    void TestInt(int a);
    void TestString(QString str);
    // 不支持
    void TestVariant(QString v);
    void TestDBUSVariant(QDBusVariant v);
    void TestListBool(QList<bool> value);
    void TestListListString(QList<QStringList> value);
    void TestListInt(QList<int> value);
    void TestListString(QStringList value);
    void TestListVariant(QList<QVariant> lists);
    void TestMapVariant(QVariantMap maps);
    void TestMapQSring(QMap<QString, QString> maps);
    void TestStruct(Persion value);
    void TestQDBusObjectPath(QDBusObjectPath value);
    void TestQDBusSignature(QDBusSignature value);
};

#endif  // DBUS_SERVER_H
