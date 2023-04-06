#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSvgRenderer>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   public slots:
    void slotSelectSVGFile();
    void slotSelectSaveFile();
    void slotDoWork();
    void slotCurrentIndexChanged(int index);

   private:
    void initUI();
    void intMenBar();
    void initConnect();

   private:
    QWidget *m_ptrWdgMain;
    QGridLayout *m_ptrGridLayoutMain;
    QLabel *m_ptrLabSVGFilePath;
    QLineEdit *m_ptrLineEditFilePath;
    QPushButton *m_ptrBtnSelectSVGFile;
    QLabel *m_ptrLabSaveFile;
    QLineEdit *m_ptrLineEditSaveFile;
    QPushButton *m_ptrBtnSaveFile;
    QPushButton *m_ptrBtnDoWork;
    QComboBox *m_ptrCmbSelectPicType;
    QSvgRenderer m_svgRenderer;
    // QMenuBar *m_ptrMenuBar;
    QMenu *m_ptrExitMenu;
    QMenu *m_ptrAbutMenu;
    int m_currentIndex;
};

#endif  // MAINWINDOW_H
