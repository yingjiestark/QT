#include "dbus_server.h"
#include <QDBusMetaType>
#include <QMap>
DBUSServer::DBUSServer(QObject *parent)
    : QObject(parent)
{
    QDBusConnection conn = QDBusConnection::sessionBus();
    bool res = conn.registerService(DBUS_NAME);
    qInfo() << "res1:" << res;
    res = conn.registerObject(DBUS_PATH, this,
                              QDBusConnection ::ExportNonScriptableSlots |
                                  QDBusConnection::ExportAllSignal);
    qInfo() << "res1:" << res;

    qDBusRegisterMetaType<Persion>();
    qDBusRegisterMetaType<QMap<QString, QString>>();
    // qDBusRegisterMetaType<QList<QString>>();
    qDBusRegisterMetaType<QList<QStringList>>();
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestInt", this,
                 SLOT(TestInt(int)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestString", this,
                 SLOT(TestString(QString)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestVraint", this,
                 SLOT(TestVraint(QVariant)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestDBUSVariant",
                 this, SLOT(TestDBUSVariant(QDBusVariant)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestListVariant",
                 this, SLOT(TestListVariant(QList<QVariant>)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestMapVariant",
                 this, SLOT(TestMapVariant(QVariantMap)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestStruct", this,
                 SLOT(TestStruct(QVariant)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestStruct", this,
                 SLOT(TestStruct(QVariant)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestListInt", this,
                 SLOT(TestListInt(QList<int>)));
    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestListString",
                 this, SLOT(TestListString(QStringList)));

    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestListBool", this,
                 SLOT(TestListBool(QList<bool>)));

    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestListListString",
                 this, SLOT(TestListListString(QList<QList<QString>>)));

    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME,
                 "TestQDBusObjectPath", this,
                 SLOT(TestQDBusObjectPath(QDBusObjectPath)));

    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestQDBusSignature",
                 this, SLOT(TestQDBusSignature(QDBusSignature)));

    conn.connect(QString(DBUS_NAME), DBUS_PATH, DBUS_NAME, "TestMapQSring",
                 this, SLOT(TestMapQSring(QMap<QString, QString>)));
}
QDBusArgument &operator<<(QDBusArgument &argument, const Persion &mystruct)
{
    argument.beginStructure();
    argument << mystruct.Name << mystruct.age;
    argument.endStructure();
    return argument;
}

// Retrieve the MyStructure data from the D-Bus argument
const QDBusArgument &operator>>(const QDBusArgument &argument,
                                Persion &mystruct)
{
    argument.beginStructure();
    argument >> mystruct.Name >> mystruct.age;
    argument.endStructure();
    return argument;
}
// 123
void DBUSServer::TestInt(int value) { qInfo() << __FUNCTION__ << value; }
// "asdf"
void DBUSServer::TestString(QString value) { qInfo() << __FUNCTION__ << value; }
/*
[__import__('gi.repository.GLib', globals(), locals(),
 ['Variant']).Variant("s", "aaa"),__import__('gi.repository.GLib', globals(),
locals(),
 ['Variant']).Variant("i", 123)]
*/
void DBUSServer::TestListVariant(QList<QVariant> lists)
{
    qInfo() << __FUNCTION__ << lists;
}
/*
 {"asdfa": __import__('gi.repository.GLib', globals(), locals(),
 ['Variant']).Variant("s", "aaa")}
 */
void DBUSServer::TestMapVariant(QVariantMap value)
{
    qInfo() << __FUNCTION__ << value;
}
/*
   {"asdf":"asdf","asdf","vvv"}
*/
void DBUSServer::TestMapQSring(QMap<QString, QString> value)
{
    qInfo() << __FUNCTION__ << value;
}
/*
 __import__('gi.repository.GLib', globals(), locals(),
 ['Variant']).Variant("(si)",("asdf",123))
 */
void DBUSServer::TestStruct(Persion value)
{
    qInfo() << __FUNCTION__ << value.Name;
    qInfo() << __FUNCTION__ << value.age;
}
// 传递路径
void DBUSServer::TestQDBusObjectPath(QDBusObjectPath value)
{
    qInfo() << __FUNCTION__ << value.path();
}
// 传递函数参数签名。传递{ss}会崩溃
void DBUSServer::TestQDBusSignature(QDBusSignature value)
{
    qInfo() << __FUNCTION__ << value.signature();
}

void DBUSServer::TestVariant(QString value)
{
    qInfo() << __FUNCTION__ << value;
}
/*
__import__('gi.repository.GLib', globals(), locals(), ['Variant']).Variant("s",
"aaa")
*/
void DBUSServer::TestDBUSVariant(QDBusVariant value)
{
    qInfo() << __FUNCTION__ << value.variant();
}
/*
 * [0,1,0,1]
 */
void DBUSServer::TestListBool(QList<bool> value)
{
    qInfo() << __FUNCTION__ << value;
}
/*
[["arr1","asdf"],["arr2","arr3"]]
*/
void DBUSServer::TestListListString(QList<QStringList> value)
{
    qInfo() << __FUNCTION__ << value;
}
// [123,312,123]
void DBUSServer::TestListInt(QList<int> value)
{
    qInfo() << __FUNCTION__ << value;
}
// ["123","312","123"]
void DBUSServer::TestListString(QStringList value)
{
    qInfo() << __FUNCTION__ << value;
}
