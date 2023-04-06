#include "main_widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QIODevice>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrLayoutMain(new QVBoxLayout(this))
    , m_ptrLayoutSelFile(new QHBoxLayout())
    , m_ptrLEFilePath(new QLineEdit())
    , m_ptrBtnSelFile(new QPushButton("选择"))
    , m_ptrTERes(new QTextEdit)
{
    initUI();
    initConnect();
}

void MainWidget::slotBtnSelFile()
{
    QFileDialog dlg;
    QString name = dlg.getOpenFileName();
    m_ptrLEFilePath->setText(name);
    QFileInfo file_info(name);
    if (!file_info.exists()) {
        qInfo() << "文件不存在！";
        return;
    }
    QFile file(name);
    if (!file.open(QFile::ReadOnly)) {
        qInfo() << "打开文件失败！";
    }
    qInfo() << "文件大小为：" << file_info.size();
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_7);
    QByteArray s = file.readAll();
    QString str;
    for (int i = 0; i < s.size(); i++) {
        QString str1 =
            QString("%1").arg(uchar(s.at(i)), 2, 16, QLatin1Char('0'));
        str1 = str1.toUpper();
        str += "0x" + str1;
        str += " ";
        if ((i + 1) % 16 == 0) {
            str += "\r\n";
        }
    }
    qInfo() << s.size();
    m_ptrTERes->setText(str);
    file.close();
}

void MainWidget::initUI()
{
    m_ptrLayoutSelFile->addWidget(m_ptrLEFilePath);
    m_ptrLEFilePath->setReadOnly(true);
    m_ptrLayoutSelFile->addWidget(m_ptrBtnSelFile);
    m_ptrLayoutSelFile->setSpacing(5);

    m_ptrLayoutMain->addLayout(m_ptrLayoutSelFile);
    m_ptrTERes->setFont(QFont("宋体", 14));
    m_ptrLayoutMain->addWidget(m_ptrTERes);
    m_ptrTERes->setReadOnly(true);
    m_ptrLayoutMain->setSpacing(5);
}

void MainWidget::initConnect()
{
    connect(m_ptrBtnSelFile, &QPushButton::clicked, this,
            &MainWidget::slotBtnSelFile);
}

void MainWidget::loadFile(QString strFilePath)
{
    if (strFilePath.isEmpty()) {
        return;
    }
}
