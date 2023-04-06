#ifndef MAINWINDOW_P_H
#define MAINWINDOW_P_H
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "numitem.h"
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include "mainwindow.h"
#include "common.h"
QT_BEGIN_NAMESPACE
class MainWindowPrivate : public QObject {
   public:
    MainWindowPrivate(MainWindow *parent);
    void initUI();
    void initConnect();
    MainWindow *const q_ptr;
    QWidget *m_wdgMain;
    // 整数分数概率控件
    QSlider *m_sliderIntegerChance;
    QLabel *m_labIntegerChance;
    QLabel *m_labIntegerChanceValue;
    QHBoxLayout *m_layoutIntegerChance;
    // 正负数概率控件
    QSlider *m_sliderPositiveChance;
    QLabel *m_labPositiveChance;
    QLabel *m_labPositiveChanceValue;
    QHBoxLayout *m_layoutPositiveChance;
    // 分子范围 1 - X
    QLineEdit *m_lineEditMoleculeRange;
    QLabel *m_labMoleculeRange;
    QHBoxLayout *m_layoutMoleculeRange;

    // 分母范围 1 - X
    QLineEdit *m_lineEditDenominatorRange;
    QLabel *m_labDenominatorRange;
    QHBoxLayout *m_layoutDenominatorRange;
    // 每一行数字
    QLineEdit *m_lineEditNum;
    QLabel *m_labNum;
    QHBoxLayout *m_layoutNum;

    // 生成试卷的页码数量
    QLineEdit *m_lineEditPage;
    QLabel *m_labPage;
    QHBoxLayout *m_layoutPage;
    // 运算符号
    QLabel *m_labAdd;
    QCheckBox *m_chkboxAdd;
    QLabel *m_labSub;
    QCheckBox *m_chkboxSub;
    QLabel *m_labMul;
    QCheckBox *m_chkboxMul;
    QLabel *m_labDiv;
    QCheckBox *m_chkboxDiv;
    QHBoxLayout *m_layoutOption;
    // 保存路径
    QPushButton *m_btnSavePath;
    QLineEdit *m_lineEditSavePath;
    QHBoxLayout *m_hlayoutSavePath;


    QPushButton *m_btnWritePDF;

    QVBoxLayout *m_vlayoutMain;

    Q_DECLARE_PUBLIC(MainWindow)
   private:
    Numrule getNumRule();

    // 绘制一条线上的1
   public slots:

    void slotIntegerChance(int value);
    void slotPositiveChance(int value);
};
QT_END_NAMESPACE
#endif  // MAINWINDOW_P_H
