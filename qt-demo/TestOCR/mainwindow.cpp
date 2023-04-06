#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_Widgetmain(new QWidget),
      m_layoutFileSelect(new QHBoxLayout()),
      m_layoutMain(new QVBoxLayout()),
      m_lineEditPath(new QLineEdit),
      m_btnSelectFile(new QPushButton),
      m_btnOrc(new QPushButton),
      m_textEditRes(new QTextEdit)
{
    m_btnSelectFile->setText("选择文件");
    m_btnOrc->setText("识别");
    m_layoutFileSelect->addWidget(m_lineEditPath);
    m_layoutFileSelect->addWidget(m_btnSelectFile);
    m_layoutFileSelect->addWidget(m_btnOrc);
    m_layoutMain->addLayout(m_layoutFileSelect);
    m_layoutMain->addWidget(m_textEditRes);
    m_Widgetmain->setLayout(m_layoutMain);

    // 设置按钮监听事件
    connect(m_btnSelectFile,&QPushButton::clicked,this,&MainWindow::slotSelectFile);
    connect(m_btnOrc,&QPushButton::clicked,this,&MainWindow::slotGetORCRes);
    setCentralWidget(m_Widgetmain);
    resize(800,600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotSelectFile()
{
    QFileDialog fileDlg;
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题",".","*.*");
    m_lineEditPath->setText(file_name);
}

void MainWindow::slotGetORCRes()
{
    char *outText;

   tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
   // Initialize tesseract-ocr with English, without specifying tessdata path
   if (api->Init(NULL, "chi_sim")) {
       fprintf(stderr, "Could not initialize tesseract.\n");
       exit(1);
   }

   // Open input image with leptonica library
   QString strPath = m_lineEditPath->text(); // 获取图片路径
   Pix *image = pixRead(strPath.toUtf8());
   api->SetImage(image);
   // Get OCR result
   outText = api->GetUTF8Text();
   qInfo()<<outText;
   printf("OCR output:\n%s", outText);
   // 显示结果
   m_textEditRes->setText(outText);
   // Destroy used object and release memory
   api->End();
   delete api;
   delete [] outText;
   pixDestroy(&image);
}
