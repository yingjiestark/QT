#ifndef PDFMANAGER_H
#define PDFMANAGER_H

#include <QObject>
#include "numitem.h"
#include "common.h"
#include "datafactory.h"
#define LINE_HEIGHT 40
class QPainter;
//
class PDFManager : public QObject {
    Q_OBJECT
   public:
    explicit PDFManager(QObject *parent = nullptr);

    int writePDF(QString file_path, Numrule rule);
    int writePDF(QString file_path, QList<QList<NumItem>> list);

    // 绘制数据
    void draw(QList<QList<NumItem>> list, QPainter *pPainter);
    // 绘制当前行的内容
    void drawLine(int index, QList<NumItem> list, QPainter *pPainter);
    // 绘制单个数字的内容给你，返回绘制该数字的长度。
    int drawNum(int index, int startPostion, NumItem item, QPainter *pPainter);
    // 获取绘制的数字的宽度
    int getNumWidth(NumItem item, QPainter *pPainter);

   private:
    DataFactory m_dataFactory;
    QList<NUMOPTION> m_list;
   signals:
};

#endif  // PDFMANAGER_H
