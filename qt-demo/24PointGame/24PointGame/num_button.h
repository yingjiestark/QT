#ifndef NUM_BUTTON_H
#define NUM_BUTTON_H

#include <QObject>
#include <QPushButton>
#include "lnum.h"
class NumButton : public QPushButton {
    Q_OBJECT
   public:
    explicit NumButton(int num, QPushButton *parent = nullptr);
    explicit NumButton(int fenzi, int fenmu, QPushButton *parent = nullptr);
    void setSelectStatus(bool status);
    bool getSelectStatus();
    void setType(int type);
    int getType();
    LNum getValue();
    void setVale(LNum num);

   private:
    bool m_status;
    int m_iType;
    LNum m_value;
   signals:

   public slots:

    // QWidget interface
   protected:
    void paintEvent(QPaintEvent *event);
};

#endif  // NUM_BUTTON_H
