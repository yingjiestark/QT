#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QtDebug>
#include <QJsonArray>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    parseObject();
    parseArray();
    parseObjectArray();
    parseArrayObject();
    buildObject();
    buildArray();
    buildObjectArray();
    buildArrayObject();
}

MainWindow::~MainWindow() {}

void MainWindow::parseObject()
{
    QString str = "{\"Name\":\"小明\",\"Age\":18}";
    QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jobject = jdoc.object();
    QJsonValue jvalue_name = jobject.value("Name");
    qInfo() << jvalue_name.toString();
    QJsonValue jvalue_age = jobject.value("Age");
    qInfo() << jvalue_age.toInt();

    ///////// 遍历 /////////////
    //  item 为QJsonValue类型
    foreach (auto item, jobject.keys()) {
        qInfo() << "key:" << item;
        QJsonValue jvalue = jobject.value(item);
        qInfo() << "value:" << jvalue.toVariant();
    }
}

void MainWindow::parseArray()
{
    QString str = "[\"apple\",\"orange\",\"banana\",\"watermelon\"]";
    QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonArray jArray = jdoc.array();
    // item 为QJsonValue类型
    foreach (auto item, jArray) {
        qInfo() << item.toString();
    }
}

void MainWindow::parseObjectArray()
{
    QString str = "{\"Lists\":[\"apple\",\"orange\"]}";
    QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jObject = jdoc.object();
    QJsonValue jLists = jObject.value("Lists");
    QJsonArray jArray = jLists.toArray();
    // item 为QJsonValue类型
    foreach (auto item, jArray) {
        qInfo() << "value:" << item.toString();
    }
}

void MainWindow::parseArrayObject()
{
    QString str =
        "[{\"Name\":\"小明\",\"age\":18},{\"Name\":\"小王\",\"age\":20}]";
    QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonArray jLists = jdoc.array();
    foreach (auto item, jLists) {
        QJsonObject item_object = item.toObject();
        qInfo() << "===============================";
        qInfo() << "name:" << item_object.value("Name").toString();
        qInfo() << "age:" << item_object.value("age").toDouble();
    }
}

void MainWindow::buildObject()
{
    QJsonObject jObject;
    QJsonDocument jDoc;
    jObject.insert("Name", "小明");
    jObject.insert("Age", 18);
    jObject.insert("Sex", QJsonValue("男"));
    jDoc.setObject(jObject);

    qInfo() << "object json:" << QString(jDoc.toJson(QJsonDocument::Compact));
}

void MainWindow::buildArray()
{
    QJsonDocument jDoc;
    QJsonArray jArray;

    jArray.append("apple");
    jArray.append("watermalon");
    jArray.append("orage");
    jDoc.setArray(jArray);
    qInfo() << "array json:" << QString(jDoc.toJson(QJsonDocument::Compact));
}

void MainWindow::buildObjectArray()
{
    QJsonDocument jDoc;
    QJsonObject jObject;
    QJsonArray jArray1;
    jArray1.append("apple");
    jArray1.append("watermalon");
    jArray1.append("orage");
    jObject.insert("水果列表", jArray1);
    jObject.insert("类型", "水果");
    jDoc.setObject(jObject);

    qInfo() << "json:" << QString(jDoc.toJson(QJsonDocument::Compact));
}

void MainWindow::buildArrayObject()
{
    QJsonDocument jDoc;
    QJsonObject jObject1;
    QJsonObject jObject2;
    QJsonArray jArray;
    jObject1.insert("Name", "小明");
    jObject1.insert("Age", 18);
    jObject1.insert("Sex", QJsonValue("男"));

    jObject2.insert("Name", "小雨");
    jObject2.insert("Age", 17);
    jObject2.insert("Sex", QJsonValue("女"));
    jArray.append(jObject1);
    jArray.append(jObject2);
    jDoc.setArray(jArray);
    qInfo() << "json:" << QString(jDoc.toJson(QJsonDocument::Compact));
}
