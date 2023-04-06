#include "main_widget.h"
#include <QTreeWidgetItem>
#include <QFileDialog>
#include <QtDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QStandardItem>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrLineEditFilePath(new QLineEdit(this))
    , m_ptrBtnOpenfile(new QPushButton("..."))
    , m_ptrBtnLink(new QPushButton("链接数据库"))
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_ptrLayoutFile(new QHBoxLayout)
    , m_ptrLayoutContent(new QHBoxLayout)
    , m_ptrTreeWdgTables(new QTreeWidget(this))
    , m_ptrTableWdgDatas(new QTableView(this))
    , db(QSqlDatabase::addDatabase("QSQLITE"))
{
    initUI();
    initConnect();
}

void MainWidget::initUI()
{
    m_ptrLineEditFilePath->setText("/home/arv000/.UBX/database/plugins1.db");
    m_ptrLayoutFile->addWidget(m_ptrLineEditFilePath);
    m_ptrLayoutFile->addWidget(m_ptrBtnOpenfile);

    m_ptrLayoutContent->addWidget(m_ptrTreeWdgTables);
    m_ptrLayoutContent->addWidget(m_ptrTableWdgDatas);
    m_ptrLayoutMain->addLayout(m_ptrLayoutFile);
    m_ptrLayoutMain->addWidget(m_ptrBtnLink);
    m_ptrLayoutMain->addLayout(m_ptrLayoutContent);
    m_ptrTreeWdgTables->setMaximumWidth(100);
    this->setLayout(m_ptrLayoutMain);
}

void MainWidget::initConnect()
{
    connect(m_ptrBtnLink, SIGNAL(clicked()), this, SLOT(slotLoadData()));
    // 打开文件
    connect(m_ptrBtnOpenfile, SIGNAL(clicked()), this, SLOT(slotOpenFile()));
    connect(m_ptrTreeWdgTables, SIGNAL(itemClicked(QTreeWidgetItem *, int)),
            this, SLOT(slotCheckTreeItem(QTreeWidgetItem *, int)));
}

void MainWidget::showTable(QString strTableName)
{
    QStandardItemModel *student_model = new QStandardItemModel();
    student_model->setHorizontalHeaderItem(
        0, new QStandardItem(QObject::tr("字段数")));
    student_model->setHorizontalHeaderItem(
        1, new QStandardItem(QObject::tr("字段名")));
    student_model->setHorizontalHeaderItem(
        2, new QStandardItem(QObject::tr("字段类型")));

    QString str = "PRAGMA table_info(" + strTableName + ")";
    QSqlQuery query;
    query.prepare(str);
    if (query.exec()) {
        int i = 0;
        qInfo() << "query.exec";
        while (query.next()) {
            student_model->setItem(
                i, 0, new QStandardItem(query.value(0).toString()));
            student_model->setItem(
                i, 1, new QStandardItem(query.value(1).toString()));
            student_model->setItem(
                i, 2, new QStandardItem(query.value(2).toString()));
            i++;
        }
    }
    m_ptrTableWdgDatas->setModel(student_model);
    m_ptrTableWdgDatas->hideColumn(0);  // don't show the ID
    m_ptrTableWdgDatas->show();
}

void MainWidget::showShowData(QString strTableName, int page, int limit)
{
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable(strTableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->select();
    m_ptrTableWdgDatas->setModel(model);
    m_ptrTableWdgDatas->hideColumn(0);  // don't show the ID
    m_ptrTableWdgDatas->show();
}

void MainWidget::slotLoadData()
{
    if (m_ptrLineEditFilePath->isEnabled()) {
        m_ptrLineEditFilePath->setEnabled(false);
        db.setDatabaseName(m_ptrLineEditFilePath->text());
        if (!db.open()) {
            return;
        }
        QStringList listTables = db.tables();
        foreach (auto itemTable, listTables) {
            QTreeWidgetItem *item = new QTreeWidgetItem(
                m_ptrTreeWdgTables, QStringList(QString(itemTable)));

            QTreeWidgetItem *sub_item =
                new QTreeWidgetItem(item, QStringList(QString("结构")));
            item->addChild(sub_item);
            QTreeWidgetItem *sub2_item =
                new QTreeWidgetItem(item, QStringList(QString("查询")));
            item->addChild(sub2_item);
        }
    } else {
        m_ptrLineEditFilePath->setEnabled(true);
        db.close();
    }
}

void MainWidget::slotOpenFile()
{
    QString strFilename = QFileDialog::getOpenFileName(this);
    m_ptrLineEditFilePath->setText(strFilename);
}

void MainWidget::slotCheckTreeItem(QTreeWidgetItem *item, int i)
{
    if (item->parent() == nullptr) {
        return;
    }

    qInfo() << item;
    qInfo() << item->parent()->text(0);
    if (item->text(0) == "结构") {
        showTable(item->parent()->text(0));
    } else if (item->text(0) == "查询") {
        showShowData(item->parent()->text(0));
    }
    qInfo() << item->text(0);
    qInfo() << i;
}
