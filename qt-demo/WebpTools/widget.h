#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QMenu;
class QAction;
#include <QImage>
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = 0);
    ~Widget();

   private:
    QString m_strFileName;
    QMenu *m_ptrMenuMain;
    QAction *m_ptrActionSavePic;  //添加子菜单使用
    QImage m_img;
    void initMenu();
   public slots:
    void slotSavePic();  // 保存图

   protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif  // WIDGET_H
