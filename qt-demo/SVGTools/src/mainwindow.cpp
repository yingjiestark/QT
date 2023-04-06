#include "mainwindow.h"
#include <QtDebug>
#include <QFileDialog>
#include <QPainter>
#include <QStandardPaths>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget())
    , m_ptrGridLayoutMain(new QGridLayout())
    , m_ptrLabSVGFilePath(new QLabel("选择"))
    , m_ptrLineEditFilePath(new QLineEdit())
    , m_ptrBtnSelectSVGFile(new QPushButton("选择svg文件"))
    , m_ptrLabSaveFile(new QLabel("保存"))
    , m_ptrLineEditSaveFile(new QLineEdit())
    , m_ptrBtnSaveFile(new QPushButton("保存图片地址"))
    , m_ptrBtnDoWork(new QPushButton("生成"))
    , m_ptrCmbSelectPicType(new QComboBox())
    //, m_ptrMenuBar(new QMenuBar())
    , m_currentIndex(0)

{
    initUI();
    intMenBar();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::slotSelectSVGFile()
{
    QString file_name = QFileDialog::getOpenFileName(
        this, "open file dialog",
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        "SVG files(*.svg)");
    m_ptrLineEditFilePath->setText(file_name);
}

void MainWindow::slotSelectSaveFile()
{
    QString filename = QFileDialog::getSaveFileName(
        this, tr("Save Image"),
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        tr("*.png;; *.bmp;;  *.jpg;; *.tif;; *.GIF"));
    if (filename.isEmpty()) {
        return;
    } else {
        m_ptrLineEditSaveFile->setText(filename);
    }
}

void MainWindow::slotDoWork()
{
    if (m_ptrLineEditFilePath->text().isEmpty()) {
        return;
    }

    m_svgRenderer.load(m_ptrLineEditFilePath->text());
    qInfo() << "m_svgRenderer" << m_svgRenderer.defaultSize();
    QPixmap _pixmapSvg =
        QPixmap(m_svgRenderer.defaultSize() * (m_currentIndex + 1));
    _pixmapSvg.fill(Qt::transparent);
    QPainter painter2(&_pixmapSvg);
    m_svgRenderer.render(&painter2, _pixmapSvg.rect());
    _pixmapSvg.scaled(m_svgRenderer.defaultSize(), Qt::IgnoreAspectRatio,
                      Qt::FastTransformation);
    _pixmapSvg.save(m_ptrLineEditSaveFile->text());

    //    _savePic.
};

void MainWindow::slotCurrentIndexChanged(int index)
{
    qInfo() << "slotCurrentIndexChanged" << index;
}

void MainWindow::initUI()
{
    setWindowTitle(tr("svg图片转化工具"));
    this->setWindowIcon(QIcon(":/svg-tools.png"));

    m_ptrLineEditFilePath->setDisabled(true);
    m_ptrLineEditSaveFile->setDisabled(true);
    m_ptrGridLayoutMain->addWidget(m_ptrLabSVGFilePath, 0, 0);
    m_ptrGridLayoutMain->addWidget(m_ptrLineEditFilePath, 0, 1);
    m_ptrGridLayoutMain->addWidget(m_ptrBtnSelectSVGFile, 0, 2);

    m_ptrGridLayoutMain->addWidget(m_ptrLabSaveFile, 1, 0);
    m_ptrGridLayoutMain->addWidget(m_ptrLineEditSaveFile, 1, 1);
    m_ptrGridLayoutMain->addWidget(m_ptrBtnSaveFile, 1, 2);
    m_ptrGridLayoutMain->addWidget(m_ptrCmbSelectPicType, 2, 0, 1, 3);

    m_ptrCmbSelectPicType->addItem(tr("原始"));
    m_ptrCmbSelectPicType->addItem(tr("2倍"));
    m_ptrCmbSelectPicType->addItem(tr("3倍"));
    m_ptrCmbSelectPicType->addItem(tr("4倍"));
    m_ptrCmbSelectPicType->addItem(tr("5倍"));
    m_ptrCmbSelectPicType->addItem(tr("6倍"));
    m_ptrCmbSelectPicType->addItem(tr("7倍"));
    m_ptrCmbSelectPicType->setCurrentIndex(4);
    m_currentIndex = 4;
    m_ptrGridLayoutMain->addWidget(m_ptrBtnDoWork, 3, 0, 1, 3);
    m_ptrWdgMain->setLayout(m_ptrGridLayoutMain);
    setMinimumSize(640, 240);
    setMaximumSize(640, 240);

    //   setMenuBar(m_ptrMenuBar);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::intMenBar()
{
    this->setStyleSheet("QMenuBar{background-color:#ccc;}");
    m_ptrAbutMenu = new QMenu(tr(" 关于 "), this);
    QAction* aboutAct = new QAction(tr("&关于"), this);
    QAction* openAct = new QAction(tr("&退出"), this);
    m_ptrAbutMenu->addAction(openAct);
    m_ptrAbutMenu->addAction(aboutAct);
    //    m_ptrMenuBar->addMenu(m_ptrAbutMenu);
    //    setMenuBar(m_ptrMenuBar);
}

void MainWindow::initConnect()
{
    connect(m_ptrBtnSelectSVGFile, SIGNAL(clicked()), this,
            SLOT(slotSelectSVGFile()));
    connect(m_ptrBtnSaveFile, SIGNAL(clicked()), this,
            SLOT(slotSelectSaveFile()));
    connect(m_ptrBtnDoWork, SIGNAL(clicked()), this, SLOT(slotDoWork()));
    connect(m_ptrCmbSelectPicType, SIGNAL(currentIndexChanged(int)), this,
            SLOT(slotCurrentIndexChanged(int)));
}
