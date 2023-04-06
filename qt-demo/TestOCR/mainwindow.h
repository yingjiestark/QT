#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QTextEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *m_Widgetmain;
    QHBoxLayout *m_layoutFileSelect;
    QVBoxLayout *m_layoutMain;
    QLineEdit *m_lineEditPath;      // 显示图片路径
    QPushButton *m_btnSelectFile;   // 文件选择按钮
    QPushButton *m_btnOrc;   // 文件选择按钮
    QTextEdit *m_textEditRes;       // 结果展示
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    // 控件按钮选择文件的事件处理
    void slotSelectFile();
    void slotGetORCRes();
};

#endif // MAINWINDOW_H
