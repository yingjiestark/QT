#include "mainwindow.h"

#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QUrl>
#include "numitem.h"
#include <QList>
#include <QDebug>
#include "mainwindow_p.h"
#include <QIntValidator>
#include <QRandomGenerator>
#include <QMessageBox>
MainWindowPrivate::MainWindowPrivate(MainWindow *parent)
    : q_ptr(parent)
    , m_wdgMain(new QWidget())
    , m_sliderIntegerChance(new QSlider())
    , m_labIntegerChance(new QLabel(tr("分整数概率：")))
    , m_labIntegerChanceValue(new QLabel("50%"))
    , m_layoutIntegerChance(new QHBoxLayout)
    , m_sliderPositiveChance(new QSlider())
    , m_labPositiveChance(new QLabel(tr("正负数概率：")))
    , m_labPositiveChanceValue(new QLabel(tr("50%")))
    , m_layoutPositiveChance(new QHBoxLayout)
    , m_lineEditMoleculeRange(new QLineEdit("10"))
    , m_labMoleculeRange(new QLabel(tr("分子值范围：")))
    , m_layoutMoleculeRange(new QHBoxLayout)
    , m_lineEditDenominatorRange(new QLineEdit("10"))
    , m_labDenominatorRange(new QLabel(tr("分母值范围：")))
    , m_layoutDenominatorRange(new QHBoxLayout)
    , m_lineEditNum(new QLineEdit("4"))
    , m_labNum(new QLabel(tr("单行数字个数：")))
    , m_layoutNum(new QHBoxLayout)
    , m_lineEditPage(new QLineEdit("10"))
    , m_labPage(new QLabel(tr("生成页码数量：")))
    , m_layoutPage(new QHBoxLayout)
    ,  m_labAdd(new QLabel(tr("加法：")))
    ,  m_chkboxAdd(new QCheckBox)
    ,  m_labSub(new QLabel(tr("减法：")))
    ,  m_chkboxSub(new QCheckBox)
    ,  m_labMul(new  QLabel(tr("乘法：")))
    ,  m_chkboxMul(new QCheckBox)
    ,  m_labDiv(new  QLabel(tr("除法：")))
    ,  m_chkboxDiv(new QCheckBox)
    , m_layoutOption(new QHBoxLayout)
    , m_btnSavePath(new QPushButton(tr("保存路径")))
    , m_lineEditSavePath(new QLineEdit())
    , m_hlayoutSavePath(new QHBoxLayout)
    , m_btnWritePDF(new QPushButton(tr("生成试卷")))
    , m_vlayoutMain(new QVBoxLayout)
{
    initUI();
    initConnect();
}

void MainWindowPrivate::initUI()
{
    //
    m_layoutIntegerChance->addWidget(m_labIntegerChance);
    m_layoutIntegerChance->addWidget(m_sliderIntegerChance);
    m_sliderIntegerChance->setValue(50);
    m_sliderIntegerChance->setMaximum(100);
    m_layoutIntegerChance->addWidget(m_labIntegerChanceValue);
    m_sliderIntegerChance->setOrientation(Qt::Orientation::Horizontal);
    m_vlayoutMain->addLayout(m_layoutIntegerChance);
    //
    m_layoutPositiveChance->addWidget(m_labPositiveChance);
    m_layoutPositiveChance->addWidget(m_sliderPositiveChance);
    m_sliderPositiveChance->setValue(50);
    m_sliderPositiveChance->setMaximum(100);
    m_layoutPositiveChance->addWidget(m_labPositiveChanceValue);
    m_sliderPositiveChance->setOrientation(Qt::Orientation::Horizontal);
    m_vlayoutMain->addLayout(m_layoutPositiveChance);
    //
    m_layoutMoleculeRange->addWidget(m_labMoleculeRange);
    m_layoutMoleculeRange->addWidget(m_lineEditMoleculeRange);
    m_lineEditMoleculeRange->setValidator(new QIntValidator(1, 1000, this));
    m_vlayoutMain->addLayout(m_layoutMoleculeRange);
    //
    m_layoutDenominatorRange->addWidget(m_labDenominatorRange);
    m_layoutDenominatorRange->addWidget(m_lineEditDenominatorRange);
    m_lineEditDenominatorRange->setValidator(new QIntValidator(1, 1000, this));
    m_vlayoutMain->addLayout(m_layoutDenominatorRange);

    m_layoutNum->addWidget(m_labNum);
    m_layoutNum->addWidget(m_lineEditNum);
    m_lineEditNum->setValidator(new QIntValidator(2, 8, this));
    m_vlayoutMain->addLayout(m_layoutNum);

    m_layoutPage->addWidget(m_labPage);
    m_layoutPage->addWidget(m_lineEditPage);
    m_lineEditPage->setValidator(new QIntValidator(1, 1000, this));
    m_vlayoutMain->addLayout(m_layoutPage);
    //  运算符操作布局
    m_layoutOption->addWidget(m_labAdd);
    m_layoutOption->addWidget(m_chkboxAdd);
    m_layoutOption->addWidget(m_labSub);
    m_layoutOption->addWidget(m_chkboxSub);
    m_layoutOption->addWidget(m_labMul);
    m_chkboxMul->setChecked(true);
    m_layoutOption->addWidget(m_chkboxMul);
    m_layoutOption->addWidget(m_labDiv);
    m_layoutOption->addWidget(m_chkboxDiv);
    m_layoutOption->addStretch();
    m_vlayoutMain->addLayout(m_layoutOption);
    //
    m_hlayoutSavePath->addWidget(m_lineEditSavePath);
    m_hlayoutSavePath->addWidget(m_btnSavePath);
    m_vlayoutMain->addLayout(m_hlayoutSavePath);

    m_vlayoutMain->addWidget(m_btnWritePDF);
    m_vlayoutMain->addStretch();
    m_wdgMain->setLayout(m_vlayoutMain);
}
void MainWindowPrivate::initConnect()
{
    connect(m_sliderIntegerChance, &QSlider::valueChanged, this,
            &MainWindowPrivate::slotIntegerChance);
    connect(m_sliderPositiveChance, &QSlider::valueChanged, this,
            &MainWindowPrivate::slotPositiveChance);

    connect(m_btnWritePDF, &QPushButton::clicked, q_ptr,
            &MainWindow::slotDoWrite);
    connect(m_btnSavePath, &QPushButton::clicked, q_ptr,
            &MainWindow::slotPickPath);
}

Numrule MainWindowPrivate::getNumRule()
{
    Numrule item;
    item.IntegerChance = m_sliderIntegerChance->value();
    item.PositiveChance = m_sliderPositiveChance->value();
    item.MoleculeRange = m_lineEditMoleculeRange->text().toInt();
    item.DenominatorRange = m_lineEditDenominatorRange->text().toInt();
    item.page = m_lineEditPage->text().toInt();
    if(m_chkboxAdd->checkState()){
        item.option.append(ADDOPTION);
    }
    if(m_chkboxSub->checkState()){
        item.option.append(SUBOPTION);
    }
    if(m_chkboxMul->checkState()){
        item.option.append(MULOPTION);
    }
    if(m_chkboxDiv->checkState()){
        item.option.append(DIVOPTION);
    }
    return item;
}

void MainWindowPrivate::slotIntegerChance(int value)
{
    QString str = QString::number(value) + "%";
    m_labIntegerChanceValue->setText(str);
}

void MainWindowPrivate::slotPositiveChance(int value)
{
    QString str = QString::number(value) + "%";
    m_labPositiveChanceValue->setText(str);
}

//=====================================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , d_ptr(new MainWindowPrivate(this))
{
    Q_D(MainWindow);
    setCentralWidget(d->m_wdgMain);
    setMinimumWidth(800);
}

MainWindow::~MainWindow()
{
    Q_D(MainWindow);
    delete d;
}

void MainWindow::slotDoWrite()
{
    Q_D(MainWindow);
    NUMRULE rule =  d->getNumRule();
    if(rule.option.size() ==0){
        QMessageBox::information(this,"警告","您未选择运算符");
        return;
    }
    QString file_path = QApplication::applicationDirPath() + "/text.pdf";
    pdfManager.writePDF(file_path, rule);
}

void MainWindow::slotPickPath() { qInfo() << "slotPickPath"; }
