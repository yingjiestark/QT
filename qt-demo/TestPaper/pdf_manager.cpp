#include "pdf_manager.h"
#include <QFile>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>
#include <QDebug>
PDFManager::PDFManager(QObject *parent)
    : QObject(parent)
{
}

int PDFManager::writePDF(QString file_path, Numrule rule)
{
    QFile pdfFile(file_path);
    pdfFile.open(QIODevice::WriteOnly);
    QPdfWriter *pWriter = new QPdfWriter(&pdfFile);
    pWriter->setPageSize(QPagedPaintDevice::A4);
    pWriter->setResolution(96);
    pWriter->setPageMargins(QMarginsF(35, 35, 35, 35));
    m_list = rule.option;
    QPainter *pPainter = new QPainter(pWriter);
    int lastPage = rule.page;
    for (int i = 0; i <= (lastPage - 1); i++) {
        QList<QList<NumItem>> list = m_dataFactory.initALLNumList(rule);
        // 获取生成数据的随机规则
        draw(list, pPainter);
        if (i != (lastPage - 1)) pWriter->newPage();
    }

    delete pPainter;
    delete pWriter;
    pdfFile.close();

    QDesktopServices::openUrl(QUrl::fromLocalFile(file_path));
    return 0;
}

void PDFManager::draw(QList<QList<NumItem>> list, QPainter *pPainter)
{
    QFontMetrics fm(pPainter->fontMetrics());
    // 绘制 填写的试卷信息。
    int w = fm.width("姓名：______________");
    pPainter->drawText(QRect(0, 0, w, fm.height()), Qt::AlignCenter,
                       QString((QString("姓名：______________"))));
    int startX = w;
    w = fm.width("日期：______________");
    pPainter->drawText(QRect(startX, 0, startX + w, fm.height()),
                       Qt::AlignCenter,
                       QString((QString("日期：______________"))));
    startX += w;
    w = fm.width("分数：______________");
    pPainter->drawText(QRect(startX, 0, startX + w, fm.height()),
                       Qt::AlignCenter,
                       QString((QString("分数：______________"))));

    // 遍历绘制每一行的数学公式
    for (int index = 1; index <= list.size(); index++) {
        drawLine(index, list.at(index - 1), pPainter);
    }
}

void PDFManager::drawLine(int index, QList<NumItem> list, QPainter *pPainter)
{
    int w = 20;
    QFontMetrics fm(pPainter->fontMetrics());
    int startNumY = (LINE_HEIGHT * index) + (fm.height() / 2) + 2;
    QString strTitle = QString::number(index);
    // 绘制提标
    strTitle.append(".");
    int titleWidth = fm.width(strTitle);
    pPainter->drawText(
        QRect(0, startNumY, 0 + titleWidth, startNumY + fm.height()),
        Qt::AlignCenter, strTitle);

    for (int i = 0; i < list.size(); i++) {
        w += drawNum(index, w, list.at(i), pPainter);
        QString strOption = m_dataFactory.RandomOption(m_list);
        int width = fm.width(strOption);
        if (i == list.size() - 1) {
            pPainter->drawText(
                QRect(w, startNumY, w + width, startNumY + fm.height()),
                Qt::AlignCenter, QString((QString("="))));
            w += width;
        } else {
            pPainter->drawText(
                QRect(w, startNumY, w + width, startNumY + fm.height()),
                Qt::AlignCenter, QString(strOption));
            w += width;
        }
    }
}
int PDFManager::drawNum(int index, int startPostionX, NumItem item,
                        QPainter *pPainter)
{
    QString str = "";
    QFontMetrics fm(pPainter->fontMetrics());
    QPen pen;
    pen.setWidth(4);
    pPainter->setPen(pen);

    // 起始的x坐标
    int startNumX = 0;
    // 起始的y坐标。
    int startNumY = 0;
    // 1. 绘制信息获取
    startNumX = startPostionX;

    if (item.getNumType() == NumItem::INTEGER) {
        startNumY = index * LINE_HEIGHT + fm.height() / 2;
    } else {
        startNumY = index * LINE_HEIGHT;
    }

    // 如果是正数
    if (item.getSymbol() == NumItem::POSITIVENUMBER) {
        // 直接绘制数字
        if (item.getNumType() == NumItem::INTEGER) {
            QString strMolecule = QString::number(item.getMolecule());
            int w = fm.width(strMolecule);
            pPainter->drawText(QRect(startNumX, startNumY, startNumX + w,
                                     startNumY + fm.height()),
                               Qt::AlignCenter, QString(strMolecule));
        } else {
            QString strMolecule = QString::number(item.getMolecule());
            QString strDenominator = QString::number(item.getDenominator());
            int w = fm.width(strMolecule);
            // 绘制分子
            pPainter->drawText(startNumX, startNumY, startNumX + w,
                               startNumY + fm.height(), Qt::AlignCenter,
                               QString(strMolecule));
            // 绘制分母
            pPainter->drawText(startNumX, startNumY + fm.height(),
                               startNumX + w, startNumY + fm.height() * 2,
                               Qt::AlignCenter, strDenominator);
            // 分号
            pPainter->drawText(
                startNumX, index * LINE_HEIGHT + fm.height() / 2, startNumX + w,
                index * LINE_HEIGHT + fm.height() / 2 + fm.height(),
                Qt::AlignCenter, QString("-"));
        }
    } else {
        int w = fm.width(QString("("));
        pPainter->drawText(
            QRect(startNumX, index * LINE_HEIGHT + fm.height() / 2,
                  startNumX + w,
                  index * LINE_HEIGHT + fm.height() / 2 + fm.height()),
            Qt::AlignCenter, QString("("));
        startNumX += w;
        w = fm.width(QString("-"));

        pPainter->drawText(
            QRect(startNumX, index * LINE_HEIGHT + fm.height() / 2,
                  startNumX + w,
                  index * LINE_HEIGHT + fm.height() / 2 + fm.height()),
            Qt::AlignCenter, QString("-"));
        startNumX += w;
        if (item.getNumType() == NumItem::INTEGER) {
            QString strMolecule = QString::number(item.getMolecule());
            int w = fm.width(strMolecule);
            pPainter->drawText(QRect(startNumX, startNumY, startNumX + w,
                                     startNumY + fm.height()),
                               Qt::AlignCenter, QString(strMolecule));
            startNumX += w;
        } else {
            QString strMolecule = QString::number(item.getMolecule());
            QString strDenominator = QString::number(item.getDenominator());
            int w = fm.width(strMolecule);
            // 绘制分子
            pPainter->drawText(QRect(startNumX, startNumY, startNumX + w,
                                     startNumY + fm.height()),
                               Qt::AlignCenter, QString(strMolecule));
            // 绘制分母
            pPainter->drawText(
                QRect(startNumX, index * LINE_HEIGHT + fm.height(),
                      startNumX + w, index * LINE_HEIGHT + fm.height() * 2),
                Qt::AlignCenter, strDenominator);

            pPainter->drawText(
                startNumX, index * LINE_HEIGHT + fm.height() / 2, startNumX + w,
                index * LINE_HEIGHT + fm.height() / 2 + fm.height(),
                Qt::AlignCenter, QString("-"));
            startNumX += w;
        }
        w = fm.width(QString(")"));
        // startNumX += w;
        pPainter->drawText(
            QRect(startNumX, index * LINE_HEIGHT + fm.height() / 2,
                  startNumX + w,
                  index * LINE_HEIGHT + fm.height() + fm.height() / 2),
            Qt::AlignCenter, QString(")"));
    }
    return getNumWidth(item, pPainter);
}

int PDFManager::getNumWidth(NumItem item, QPainter *pPainter)
{
    // 1. 获取纯数字的宽度。
    QFontMetrics fm(pPainter->fontMetrics());
    int numWidth = 0;
    // 2. 分数判断
    if (item.getNumType() == NumItem::INTEGER) {
        //  如果其为整数直接获取数字的长度
        numWidth = fm.width(QString::number(item.getMolecule()));
    } else {
        // 如果为分数
        int iWidthMolecule = fm.width(QString::number(item.getMolecule()));
        int iWidthDenominator =
            fm.width(QString::number(item.getDenominator()));
        numWidth = iWidthMolecule > iWidthDenominator ? iWidthMolecule
                                                      : iWidthDenominator;
    }
    // 3. 正负数判断
    if (item.getSymbol() == NumItem::NEGATIVENUMBER) {
        int iWidthKL = fm.width(QString("("));
        int iWidthSymbol = fm.width(QString("-"));
        int iWidthKR = fm.width(QString(")"));
        numWidth += iWidthSymbol;
        numWidth += iWidthKL;
        numWidth += iWidthKR;
    }
    return numWidth;
}
