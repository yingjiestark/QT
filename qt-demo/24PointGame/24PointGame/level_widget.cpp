#include "level_widget.h"
#include <QPushButton>
#include <QVariant>
#include <QtDebug>
#include "db/dbmanager.h"
#include "level_button.h"
LevelWidget::LevelWidget(QWidget *parent)
    : QWidget(parent)
{
}

LevelWidget::LevelWidget(int start, int end)
    : m_layoutMain(new QGridLayout)
{
    int row = 0;
    for (int i = start; i <= end; i++) {
        // 获取单个关卡的内容
        ModeItem item = DBManager::getInstance()->getLevelData(i);
        LevelButton *btn = new LevelButton(i);
        // qInfo() << "item.status" << item.status << "sa" << (item.status ==
        // 0);
        if (item.status == 0) {
            btn->setLockStatus(true);
        } else {
            btn->setLockStatus(false);
        }
        btn->setProperty("id", QVariant::fromValue(i));
        m_layoutMain->addWidget(btn, row, (i - 1) % 5);

        if (i % 5 == 0) {
            row++;
        }

        connect(btn, SIGNAL(clicked()), this, SLOT(slotBtnClick()));
    }
    setLayout(m_layoutMain);
}

void LevelWidget::unLockLevel(int level)
{
    level = (level - 1) % 25 + 1;
    int row = (level - 1) == 0 ? 0 : int((level - 1) / 5);
    int col = (level - 1) % 5;
    QLayoutItem *pLayout =
        (QLayoutItem *)m_layoutMain->itemAtPosition(row, col);
    LevelButton *btn = dynamic_cast<LevelButton *>(pLayout->widget());
    btn->setUnlock();
}

void LevelWidget::slotBtnClick()
{
    LevelButton *btn = ((LevelButton *)sender());
    QVariant value = btn->property("id");
    int level = value.value<int>();
    if (btn->getLockStatus()) {
        return;
    }
    emit sigBtnClick(level);
    qInfo() << "value:" << value;
}
