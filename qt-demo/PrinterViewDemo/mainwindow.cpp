#include "mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainLayout(new QHBoxLayout(this))
    , m_main(new QWidget(this))
    , m_btn(new QPushButton("打印预览", m_main))

{
    m_main->setLayout(m_mainLayout);
    m_mainLayout->addWidget(m_btn);
    connect(m_btn, &QPushButton::clicked, this, &MainWindow::clickPrinter);
    setCentralWidget(m_main);
}

void MainWindow::clickPrinter()
{
    QPrinter printer;
    //----------------- 设置打印机属性 -------------
    // 打印预览不生效
    printer.setDuplex(QPrinter::DuplexLongSide);
    printer.setPageSize(QPrinter::A3);
    // 打印预览生效
    printer.setDoubleSidedPrinting(true);
    printer.setOrientation(QPrinter::Landscape);
    printer.setNumCopies(5);
    printer.setFromTo(2, 5);
    QPrintPreviewDialog pdlg(&printer);
    // 打印绘制消息
    connect(&pdlg, SIGNAL(paintRequested(QPrinter *)),
            SLOT(slotPrintReviewPaint(QPrinter *)));
    pdlg.exec();
}

void MainWindow::slotPrintReviewPaint(QPrinter *printer)
{
    QPainter p(printer);
    int pageNum = 5;
    for (int i = 0; i < pageNum; i++) {
        if (i != 0) printer->newPage();  // 支持多页打印
        p.drawText(100, 100, "asdfa" + QString::number(i));
    }
}

MainWindow::~MainWindow() {}
