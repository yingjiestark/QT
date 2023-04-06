#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTreeWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlDatabase>
class MainWidget : public QWidget {
    Q_OBJECT
   public:
    explicit MainWidget(QWidget *parent = nullptr);
    QLineEdit *m_ptrLineEditFilePath;
    QPushButton *m_ptrBtnOpenfile;
    QPushButton *m_ptrBtnLink;
    QVBoxLayout *m_ptrLayoutMain;
    QHBoxLayout *m_ptrLayoutFile;
    QHBoxLayout *m_ptrLayoutContent;
    QTreeWidget *m_ptrTreeWdgTables;
    QTableView *m_ptrTableWdgDatas;
    QSqlDatabase db;

   private:
    void initUI();
    void initConnect();
    void showTable(QString strTableName);
    void showShowData(QString strTableName, int page = 1, int limit = 10);
   signals:

   public slots:
    void slotLoadData();
    void slotOpenFile();
    void slotCheckTreeItem(QTreeWidgetItem *, int);
};

#endif  // MAIN_WIDGET_H
