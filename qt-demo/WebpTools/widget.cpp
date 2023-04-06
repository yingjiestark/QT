#include "widget.h"
#include <QImage>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPalette>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_strFileName("")
{
    setWindowTitle("webp图片转换器");
    setAcceptDrops(true);
    setAutoFillBackground(true);
    initMenu();
}

Widget::~Widget() {}

void Widget::initMenu()
{
    m_ptrMenuMain = new QMenu(this);         //添加菜单
    m_ptrActionSavePic = new QAction(this);  //添加子菜单
    m_ptrActionSavePic->setText("另存为");
    m_ptrMenuMain->addAction(m_ptrActionSavePic);
    connect(m_ptrActionSavePic, SIGNAL(triggered()), this, SLOT(slotSavePic()));
}

/**
 * @brief Widget::slotSavePic
 */
void Widget::slotSavePic()
{
    QString file_path = QFileDialog::getSaveFileName(
        this, "save file", "",
        "bmp files (*.bmp);;png files (*.png);;jpWg "
        "files (*.jpg)");
    qInfo() << "file_path：" << file_path;
    m_img.save(file_path);
    QMessageBox::information(this, "提示", "保存成功");
}

void Widget::dropEvent(QDropEvent *event)
{
    const QMimeData *qm = event->mimeData();  //获取MIMEData
    // qDebug()<<"drop file Name:"<<qm->urls()[0].toLocalFile();
    m_strFileName = qm->urls()[0].toLocalFile();  //获取拖入的文件名
    m_img.load(m_strFileName);
    QPalette palette;
    palette.setBrush(QPalette::Background,
                     QBrush(QPixmap(m_strFileName).scaled(size())));
    this->setPalette(palette);
    // loadFile(m_strFileName);  //依据文件名导入文件即可
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    m_ptrMenuMain->exec(QCursor::pos());  //在光标当前位置处出现
    event->accept();
}
