#include "game_widget.h"
#include "db/dbmanager.h"
#include <QVariant>
#include <QMessageBox>
#include "tools.h"
#include <QtDebug>
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_ptrLayoutBtn(new QHBoxLayout)
    , m_ptrLabTitle(new QLabel(this))
    , m_ptrLayoutGame(new QGridLayout)
    , m_ptrBtnBack(new QPushButton("返回"))
    , m_ptrBtnInitGame(new QPushButton("重新开始"))
    , m_iCurrentLevel(1)
{
    initUI();
    intiConnect();
    initGame();
}

void GameWidget::setCurrentLevel(int level)
{
    m_iCurrentLevel = level;

    initGame();
}

void GameWidget::initUI()
{
    m_ptrLayoutBtn->addWidget(m_ptrBtnBack);
    m_ptrLayoutBtn->addWidget(m_ptrBtnInitGame);
    m_ptrLayoutMain->addLayout(m_ptrLayoutBtn);
    m_ptrLayoutMain->addWidget(m_ptrLabTitle);
    m_ptrBtnNum1 = new NumButton(8);
    m_ptrBtnNum1->setType(0);
    m_ptrBtnNum2 = new NumButton(3);
    m_ptrBtnNum2->setType(1);
    m_ptrBtnNum3 = new NumButton(1);
    m_ptrBtnNum3->setType(2);
    m_ptrBtnNum4 = new NumButton(1);
    m_ptrBtnNum4->setType(3);
    m_ptrBtnOption1 = new QPushButton("+");
    m_ptrBtnOption1->setProperty("type", QVariant::fromValue(0));
    m_ptrBtnOption2 = new QPushButton("-");
    m_ptrBtnOption2->setProperty("type", QVariant::fromValue(1));
    m_ptrBtnOption3 = new QPushButton("*");
    m_ptrBtnOption3->setProperty("type", QVariant::fromValue(2));
    m_ptrBtnOption4 = new QPushButton("/");
    m_ptrBtnOption4->setProperty("type", QVariant::fromValue(3));

    m_ptrBtnNum1->setFixedSize(200, 200);
    m_ptrBtnNum2->setFixedSize(200, 200);
    m_ptrBtnNum3->setFixedSize(200, 200);
    m_ptrBtnNum4->setFixedSize(200, 200);
    QFont f("宋体", 50);
    m_ptrBtnNum1->setFont(f);
    m_ptrBtnNum2->setFont(f);
    m_ptrBtnNum3->setFont(f);
    m_ptrBtnNum4->setFont(f);

    m_ptrBtnOption1->setFixedSize(50, 200);

    m_ptrBtnOption4->setFixedSize(50, 200);

    m_ptrLayoutGame->addWidget(m_ptrBtnNum1, 0, 0);
    m_ptrLayoutGame->addWidget(m_ptrBtnOption1, 0, 1);
    m_ptrLayoutGame->addWidget(m_ptrBtnNum2, 0, 2);

    m_ptrLayoutGame->addWidget(m_ptrBtnOption2, 1, 0);
    m_ptrLayoutGame->addWidget(m_ptrBtnOption3, 1, 2);

    m_ptrLayoutGame->addWidget(m_ptrBtnNum3, 2, 0);
    m_ptrLayoutGame->addWidget(m_ptrBtnOption4, 2, 1);
    m_ptrLayoutGame->addWidget(m_ptrBtnNum4, 2, 2);

    m_ptrLayoutMain->addLayout(m_ptrLayoutGame);
    setLayout(m_ptrLayoutMain);
}

void GameWidget::intiConnect()
{
    connect(m_ptrBtnBack, &QPushButton::clicked, this,
            &GameWidget::slotBtnBack);

    connect(m_ptrBtnNum1, &NumButton::clicked, this,
            &GameWidget::slotBtnClickNum);
    connect(m_ptrBtnNum2, &NumButton::clicked, this,
            &GameWidget::slotBtnClickNum);
    connect(m_ptrBtnNum3, &NumButton::clicked, this,
            &GameWidget::slotBtnClickNum);
    connect(m_ptrBtnNum4, &NumButton::clicked, this,
            &GameWidget::slotBtnClickNum);

    connect(m_ptrBtnOption1, &QPushButton::clicked, this,
            &GameWidget::slotBtnClickOption);
    connect(m_ptrBtnOption2, &QPushButton::clicked, this,
            &GameWidget::slotBtnClickOption);
    connect(m_ptrBtnOption3, &QPushButton::clicked, this,
            &GameWidget::slotBtnClickOption);
    connect(m_ptrBtnOption4, &QPushButton::clicked, this,
            &GameWidget::slotBtnClickOption);

    connect(m_ptrBtnInitGame, &QPushButton::clicked, this,
            &GameWidget::slotBtnClickInitGame);
}

void GameWidget::initGame()
{
    DBManager::getInstance()->getAllData();
    ModeItem item = DBManager::getInstance()->getLevelData(m_iCurrentLevel);
    m_listNumSelect.clear();
    m_listOptionSelect.clear();
    m_ptrBtnNum1->show();
    m_ptrBtnNum1->setSelectStatus(false);
    m_ptrBtnNum1->setVale(LNum(item.num1));
    m_ptrBtnNum2->show();
    m_ptrBtnNum2->setSelectStatus(false);
    m_ptrBtnNum2->setVale(LNum(item.num2));
    m_ptrBtnNum3->show();
    m_ptrBtnNum3->setSelectStatus(false);
    m_ptrBtnNum3->setVale(LNum(item.num3));
    m_ptrBtnNum4->show();
    m_ptrBtnNum4->setSelectStatus(false);
    m_ptrBtnNum4->setVale(LNum(item.num4));
    m_ptrLabTitle->setText("当前第" + QString::number(m_iCurrentLevel) + "关");
}

void GameWidget::jisuan()
{
    LNum num =
        Tools::jisuan(m_listNumSelect.first().num, m_listNumSelect.last().num,
                      m_listOptionSelect.at(0).type);
    m_listNumSelect.first().btn->hide();
    m_listNumSelect.last().btn->setVale(num);
    m_listNumSelect.last().btn->setSelectStatus(false);
    m_listNumSelect.clear();
    m_listOptionSelect.clear();
    int s1 = m_ptrBtnNum1->isHidden() ? 0 : 1;
    int s2 = m_ptrBtnNum2->isHidden() ? 0 : 1;
    int s3 = m_ptrBtnNum3->isHidden() ? 0 : 1;
    int s4 = m_ptrBtnNum4->isHidden() ? 0 : 1;
    int s = s1 + s2 + s3 + s4;
    bool isWin = false;
    if (s == 1) {
        if (1 == s1 && m_ptrBtnNum1->getValue() == LNum(24)) {
            isWin = true;
        } else if (1 == s2 && m_ptrBtnNum2->getValue() == LNum(24)) {
            isWin = true;
        } else if (1 == s3 && m_ptrBtnNum3->getValue() == LNum(24)) {
            isWin = true;
        } else if (1 == s4 && m_ptrBtnNum4->getValue() == LNum(24)) {
            isWin = true;
        }
        if (isWin) {
            QMessageBox::information(this, "恭喜", "通关");
            m_iCurrentLevel++;
            DBManager::getInstance()->unlockLevel(m_iCurrentLevel);
            initGame();
            emit sigUnlockLevel(m_iCurrentLevel);
        } else {
            QMessageBox::information(this, "提示", "重新来吧");
        }
    }
}

void GameWidget::slotBtnBack() { emit sigBtnBack(); }

void GameWidget::slotBtnClickNum()
{
    NumButton *btn = (NumButton *)sender();
    // 1.判断数字按钮是否已经在列表中,如果在列表中那么移除列表。
    for (NumItem item : m_listNumSelect) {
        if (btn->getValue() == item.num && item.type == btn->getType()) {
            btn->setSelectStatus(false);
            m_listNumSelect.removeOne(item);
            return;
        }
    }
    if (m_listNumSelect.size() < 2) {
        NumItem item;
        item.type = btn->getType();
        item.num = btn->getValue();
        item.btn = btn;
        m_listNumSelect.append(item);
        btn->setSelectStatus(!btn->getSelectStatus());
    }
    // 2. 判断列表是否大于2，如果大于2
    if (m_listNumSelect.size() == 2) {
        if (m_listOptionSelect.size() == 1) {
            jisuan();
        }
    }
}

void GameWidget::slotBtnClickOption()
{
    QPushButton *btn = (QPushButton *)sender();
    int type = btn->property("type").value<int>();
    if (m_listOptionSelect.size() == 1) {
        if (m_listNumSelect.size() == 2) {
            jisuan();
        }
        return;
    } else {
        OptionItem item;
        item.type = type;
        item.option = type;
        m_listOptionSelect.append(item);
    }
}

void GameWidget::slotBtnClickInitGame() { initGame(); }
