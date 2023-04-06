#ifndef SREACH_WIDGET_H
#define SREACH_WIDGET_H

#include <QWidget>
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QLineEdit;
class QLabel;
class QTableView;
class QStandardItemModel;
class QPushButton;
#include "net/network_util.h"
#include "common.h"
class SreachWidget : public QWidget {
    Q_OBJECT

   public:
    explicit SreachWidget(QWidget *parent = nullptr);

   private:
    QLabel *m_ptrLabSreach;             // 搜索框的提示
    QLineEdit *m_ptrEdtSreach;          // 搜索框，获取用户输入的搜索内容
    QPushButton *m_ptrBtnSreach;        // 搜索按钮，点击后获取搜索到的搜索列表
    QHBoxLayout *m_ptrLayoutSreach;     // 第一行的布局
    QTableView *m_ptrTbvShowData;       // 展示搜索数据的列表
    QHBoxLayout *m_ptrLayoutTableView;  //

    QLabel *m_ptrLabTotalPage;          // 展示总页面数据。搜索的数据的按照分页的总也
    QPushButton *m_ptrBtnLastPage;      // 翻页，显示上一页
    QLineEdit *m_ptrLabCurrentPage;     // 展示当前页码
    QPushButton *m_ptrBtnNextPage;      // 翻页，显示下一页
    QPushButton *m_ptrBtnJumpPage;      // 跳转到指定页码
    QHBoxLayout *m_ptrLayoutTurnPage;   // 页码按钮布局
    QVBoxLayout *m_ptrLayoutMain;

    QStandardItemModel *m_ptrModel;

    NetworkUtil netUtil;                // 网络请求工具，用于搜索和下载音乐等。

   private:
    int m_current;           // 保存当前页码
    QString m_strSreachKey;  // 保存当前的关键词
   private:
    void initUI();
    void initConnect();
    void updateCurrentPage();  // 更新当前页码
   signals:
    // 下载完成后发送该信号。
    void sigDownLoadFinish(AbsListLocal info);
   public slots:
    void clickBtn();
    void slotLastPage();        // 响应上一页按钮
    void slotNextPage();            // 响应下一页按钮。
    void slotSreachList(SreachListInfo info);
    void onTableBtnClicked();
    void slotDownLoadFinish(AbsListLocal info);
};

#endif  // SREACH_WIDGET_H
