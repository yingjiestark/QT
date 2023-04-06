#include "sreach_widget.h"
#include <QPushButton>
#include <QtDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include "db/db_manager.h"
SreachWidget::SreachWidget(QWidget* parent)
    : QWidget(parent)
    , m_ptrLabSreach(new QLabel(this))
    , m_ptrEdtSreach(new QLineEdit(this))
    , m_ptrBtnSreach(new QPushButton(this))
    , m_ptrLayoutSreach(new QHBoxLayout())
    , m_ptrTbvShowData(new QTableView(this))
    , m_ptrLayoutTableView(new QHBoxLayout())
    , m_ptrLabTotalPage(new QLabel(this))
    , m_ptrBtnLastPage(new QPushButton(tr("上一页"), this))
    , m_ptrLabCurrentPage(new QLineEdit(this))
    , m_ptrBtnNextPage(new QPushButton(tr("下一页"), this))
    , m_ptrBtnJumpPage(new QPushButton(tr("跳转"), this))
    , m_ptrLayoutTurnPage(new QHBoxLayout)
    , m_ptrLayoutMain(new QVBoxLayout())
    , m_ptrModel(new QStandardItemModel(this))
    , m_current(0)
    , m_strSreachKey("")
{
    initUI();
    initConnect();
}

void SreachWidget::initUI()
{
    m_ptrBtnSreach->setText("搜索");
    m_ptrLabSreach->setText("请输入:");
    m_ptrEdtSreach->setText("周杰伦");
    m_ptrLayoutSreach->addWidget(m_ptrLabSreach);
    m_ptrLayoutSreach->addWidget(m_ptrEdtSreach);
    m_ptrLayoutSreach->addWidget(m_ptrBtnSreach);

    m_ptrModel->setColumnCount(4);
    m_ptrModel->setHeaderData(0, Qt::Horizontal, "音乐名称");
    m_ptrModel->setHeaderData(1, Qt::Horizontal, "演唱者");
    m_ptrModel->setHeaderData(2, Qt::Horizontal, "歌曲标号");
    m_ptrModel->setHeaderData(3, Qt::Horizontal, "下载");
    m_ptrTbvShowData->setModel(m_ptrModel);
    m_ptrLayoutTableView->addWidget(m_ptrTbvShowData);
    m_ptrLabTotalPage->setText("一共X页");
    m_ptrLayoutTurnPage->addWidget(m_ptrBtnLastPage);
    m_ptrLabCurrentPage->setMaximumWidth(200);
    m_ptrLayoutTurnPage->addWidget(m_ptrLabCurrentPage);
    m_ptrLayoutTurnPage->addWidget(m_ptrBtnNextPage);
    m_ptrLayoutTurnPage->addWidget(m_ptrBtnJumpPage);

    m_ptrLayoutTurnPage->addWidget(m_ptrLabTotalPage);

    m_ptrLayoutMain->addLayout(m_ptrLayoutSreach);
    m_ptrLayoutMain->addLayout(m_ptrLayoutTableView);
    m_ptrLayoutMain->addLayout(m_ptrLayoutTurnPage);

    setLayout(m_ptrLayoutMain);
}

void SreachWidget::initConnect()
{
    connect(m_ptrBtnSreach, &QPushButton::clicked, this,
            &SreachWidget::clickBtn);
    connect(m_ptrBtnLastPage, &QPushButton::clicked, this,
            &SreachWidget::slotLastPage);
    connect(m_ptrBtnNextPage, &QPushButton::clicked, this,
            &SreachWidget::slotNextPage);
    connect(&netUtil, &NetworkUtil::sigSearchList, this,
            &SreachWidget::slotSreachList);
    connect(&netUtil, &NetworkUtil::sigDownLoadFinish, this,
            &SreachWidget::slotDownLoadFinish);
}

void SreachWidget::updateCurrentPage()
{
    m_ptrLabCurrentPage->setText(QString::number(m_current + 1));
}

void SreachWidget::clickBtn()
{
    qInfo() << "clickBtn";
    QString name = m_ptrEdtSreach->text();
    m_strSreachKey = name;
    netUtil.postSreach(m_strSreachKey, m_current);
    updateCurrentPage();
}

void SreachWidget::slotLastPage()
{
    m_current--;
    if (m_current < 0) {
        m_current = 0;
    }
    netUtil.postSreach(m_strSreachKey, m_current);
    updateCurrentPage();
}

void SreachWidget::slotNextPage()
{
    m_current++;

    netUtil.postSreach(m_strSreachKey, m_current);
    updateCurrentPage();
}

void SreachWidget::slotSreachList(SreachListInfo info)
{
    qInfo() << "slotSreachList";
    qInfo() << info.total;
    int row = 0;
    foreach (auto item, info.absList) {
        m_ptrModel->setItem(row, 0, new QStandardItem(item.NAME));
        m_ptrModel->setItem(row, 1, new QStandardItem(item.ARTIST));
        m_ptrModel->setItem(row, 2, new QStandardItem(item.MUSICRID));
        QPushButton* button = new QPushButton("下载");
        QVariant AbsListInfo;
        AbsListInfo = QVariant::fromValue(item);
        button->setProperty("AbsList", AbsListInfo);
        button->setFocusPolicy(Qt::NoFocus);
        m_ptrTbvShowData->setIndexWidget(m_ptrModel->index(row, 3), button);
        connect(button, SIGNAL(clicked()), this, SLOT(onTableBtnClicked()));

        row++;
    }

    int totalPage = info.total / 10;
    m_ptrLabTotalPage->setText("一共" + QString::number(totalPage) + "页");
}

void SreachWidget::onTableBtnClicked()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    AbsList AbsListInfo = button->property("AbsList").value<AbsList>();

    qInfo() << AbsListInfo.MUSICRID;
    QList<AbsListLocal> temp =
        DBManager::instance()->getInfoFromRId(AbsListInfo.MUSICRID);
    if (temp.size() != 0) {
        QMessageBox::information(this, "提示", "音乐已下载");
    }
    netUtil.postDownloadMuisc(AbsListInfo);
}

void SreachWidget::slotDownLoadFinish(AbsListLocal info)
{
    emit sigDownLoadFinish(info);
}
