#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QTextEdit;

class MainWidget : public QWidget {
    Q_OBJECT
   public:
    explicit MainWidget(QWidget *parent = nullptr);

   signals:

   public slots:
    // 选择文件
    void slotBtnSelFile();

   private:
    void initUI();
    void initConnect();
    void loadFile(QString strFilePath);
    QVBoxLayout *m_ptrLayoutMain;

    QHBoxLayout *m_ptrLayoutSelFile;
    // 文件路劲
    QLineEdit *m_ptrLEFilePath;
    // 选择文件
    QPushButton *m_ptrBtnSelFile;
    // 显示结果
    QTextEdit *m_ptrTERes;
};

#endif  // MAIN_WIDGET_H
