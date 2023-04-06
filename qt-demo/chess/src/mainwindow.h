#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "chess_backgroud.h"
#include "chess_man.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsView *m_ptrMainView;
    QGraphicsScene *m_ptrMainScene;
    ChessBackgroud *nk;
    QList<Chessman *> m_lstChess;
    RoleType m_Role;
    GameType m_gameType;
    void initGameData();  // 初始化游戏数据，将数据回退到初始状态
    QPoint
    getSelectedChess();  // 是否已经有棋子已经被选中，false表示为选中，true表示有棋子选中。

    RoleType getRole();  // 获取当前的角色
    QPoint getChessboardCoordinates(int mouse_x,
                                    int mouse_y);  // 通过鼠标获取棋盘的坐标点。
    // 选中指定坐标的棋子
    void clearSelectChess();
    void selectChess(int x, int y);
    Chessman *getChess(int x, int y);  // 通过坐标获取棋子。
    void MoveChess(Chessman *chess, int x, int y);
    void MoveData(Chessman *chess, int x, int y);
    bool MoveBindR(Chessman *chess, int x, int y);
    bool MoveBindB(Chessman *chess, int x, int y);
    bool MoveXiangR(Chessman *chess, int x, int y);
    bool MoveXiangB(Chessman *chess, int x, int y);
    bool MoveShiR(Chessman *chess, int x, int y);
    bool MoveShiB(Chessman *chess, int x, int y);
    bool MoveChe(Chessman *chess, int x, int y);
    bool MoveMa(Chessman *chess, int x, int y);
    bool MovePao(Chessman *chess, int x, int y);
    bool MoveJiangR(Chessman *chess, int x, int y);
    bool MoveJiangB(Chessman *chess, int x, int y);
    GameType gameOver();

   protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif  // MAINWINDOW_H
