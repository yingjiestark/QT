#include "mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include "chess_man.h"
#include "common.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrMainView(new QGraphicsView)
    , m_ptrMainScene(new QGraphicsScene)
    , m_Role(Red)  // 初始化为红色，红色先行
    , m_gameType(running)
{
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle(tr("中国象棋"));
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    m_ptrMainView->setFixedSize(clientRect.height() - 200,
                                clientRect.height() - 200);
    g_game_width = clientRect.height() - 200;
    g_cell_width = (g_game_width) / 10;
    g_top = (g_game_width - 8 * g_cell_width) / 2;
    g_left = (g_game_width - 9 * g_cell_width) / 2;
    g_chess_man_width = g_game_width / 13;
    nk = new ChessBackgroud(clientRect.height() - 200);

    m_ptrMainScene->addItem(nk);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            if (NullChess == maps[i][j]) {
                continue;
            }
            Chessman *chessman3 = new Chessman(
                clientRect.height() - 200, static_cast<ChessType>(maps[i][j]));
            chessman3->Move(j, i);
            m_lstChess.push_back(chessman3);
            m_ptrMainScene->addItem(chessman3);
        }
    }
    // m_ptrMainScene->clear();
    m_ptrMainView->setScene(m_ptrMainScene);
    setCentralWidget(m_ptrMainView);
    this->setMouseTracking(true);
}

MainWindow::~MainWindow() {}

void MainWindow::initGameData()
{
    m_Role = Red;
    m_gameType = running;
}

QPoint MainWindow::getSelectedChess()
{
    int x = -1, y = -1;
    for (auto item : m_lstChess) {
        if (item->getSelectedStatus()) {
            x = item->getX();
            y = item->getY();
        }
    }
    return QPoint(x, y);
}

RoleType MainWindow::getRole() { return m_Role; }

QPoint MainWindow::getChessboardCoordinates(int mouse_x, int mouse_y)
{
    int x = -1, y = -1;
    int half_chess_man_width = g_chess_man_width / 2;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            int x1 = g_top + i * g_cell_width - half_chess_man_width;
            int y1 = g_left + j * g_cell_width - half_chess_man_width;

            int x2 = g_top + i * g_cell_width + half_chess_man_width;
            int y2 = g_left + j * g_cell_width + half_chess_man_width;

            if (mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 &&
                mouse_y <= y2) {
                x = i;
                y = j;
                break;
            }
        }
    }
    return QPoint(x, y);
}

void MainWindow::clearSelectChess()
{
    for (auto item : m_lstChess) {
        item->setSelectedStatus(false);
    }
}

void MainWindow::selectChess(int x, int y)
{
    clearSelectChess();
    for (auto item : m_lstChess) {
        // 找到对应的棋子，并且判断他是否存活。如果存活才能被选择。
        if (x == item->getX() && y == item->getY() && item->getLive()) {
            // 需要判断其是否为红色。
            if (m_Role == Red && item->getChessType() <= Bing_R) {
                item->setSelectedStatus(true);
            } else if (m_Role == Black && item->getChessType() > Bing_R) {
                item->setSelectedStatus(true);
            }
        }
    }
}

Chessman *MainWindow::getChess(int x, int y)
{
    for (auto item : m_lstChess) {
        if (x == item->getX() && y == item->getY()) {
            return item;
        }
    }
    return nullptr;
}

void MainWindow::MoveChess(Chessman *chess, int x, int y)
{
    bool res = false;
    switch (chess->getChessType()) {
        case Bing_R:
            res = MoveBindR(chess, x, y);
            break;
        case Bing_B:
            res = MoveBindB(chess, x, y);
            break;
        case Ma_B:
        case Ma_R:
            res = MoveMa(chess, x, y);
            break;
        case Xiang_B:
            res = MoveXiangB(chess, x, y);
            break;
        case Xiang_R:
            res = MoveXiangR(chess, x, y);
            break;
        case Shi_R:
            res = MoveShiR(chess, x, y);
            break;
        case Shi_B:
            res = MoveShiB(chess, x, y);
            break;
        case Che_B:
        case Che_R:
            res = MoveChe(chess, x, y);
            break;
        case Pao_B:
        case Pao_R:
            res = MovePao(chess, x, y);
            break;
        case Jiang_B:
            res = MoveJiangB(chess, x, y);
            break;
        case Jiang_R:
            res = MoveJiangR(chess, x, y);
            break;
        default:
            break;
    }
    if (res) {
        MoveData(chess, x, y);
        if (m_Role == Red) {
            m_Role = Black;
        } else {
            m_Role = Red;
        }
        chess->setSelectedStatus(false);
    }
    GameType gameType = gameOver();
    if (gameType != running) {
        if (gameType == Red_win) {
            QMessageBox::information(nullptr, "提示", "游戏结束，红方获胜！");
        } else {
            QMessageBox::information(nullptr, "提示", "游戏结束，黑方获胜！");
        }
    }
}

void MainWindow::MoveData(Chessman *chess, int x, int y)
{
    Chessman *tempchess = getChess(x, y);
    if (tempchess != nullptr) {
        tempchess->setLive(false);
    }
    chess->Move(x, y);
}

bool MainWindow::MoveBindR(Chessman *chess, int x, int y)
{
    bool res = false;
    if (y > 4) {
        if (chess->getY() == y + 1 && x == chess->getX()) {
            res = true;
        }
    } else {
        if (chess->getX() == x && chess->getY() == y + 1) {
            res = true;
        }
        if ((chess->getX() == x + 1 || chess->getX() == x - 1) &&
            chess->getY() == y) {
            res = true;
        }
    }
    return res;
}

bool MainWindow::MoveBindB(Chessman *chess, int x, int y)
{
    bool res = false;
    if (y < 5) {
        // 没有过河前，只能向前走
        if (chess->getY() == y - 1 && x == chess->getX()) {
            res = true;
        }
    } else {
        if (chess->getX() == x && chess->getY() == y - 1) {
            res = true;
        }
        if ((chess->getX() == x + 1 || chess->getX() == x - 1) &&
            chess->getY() == y) {
            res = true;
        }
    }
    return res;
}

bool MainWindow::MoveXiangR(Chessman *chess, int x, int y)
{
    bool res = false;
    if (abs(chess->getX() - x) == 2 && 2 == abs(chess->getY() - y) && y >= 5) {
        res = true;
        // 塞象眼
        Chessman *tempchess = nullptr;
        int tempx = (chess->getX() + x) / 2;
        int tempy = (chess->getY() + y) / 2;
        tempchess = getChess(tempx, tempy);
        if (tempchess != nullptr) {
            res = false;
        }
    }
    return res;
}

bool MainWindow::MoveXiangB(Chessman *chess, int x, int y)
{
    bool res = false;
    if (abs(chess->getX() - x) == 2 && 2 == abs(chess->getY() - y) && y <= 4) {
        res = true;
        Chessman *tempchess = nullptr;
        int tempx = (chess->getX() + x) / 2;
        int tempy = (chess->getY() + y) / 2;
        tempchess = getChess(tempx, tempy);
        if (tempchess != nullptr) {
            res = false;
        }
    }
    return res;
}

bool MainWindow::MoveShiR(Chessman *chess, int x, int y)
{
    bool res = false;
    if (abs(chess->getX() - x) == 1 && abs(chess->getY() - y) == 1 && x >= 3 &&
        x <= 5 && y >= 7) {
        res = true;
    }
    return res;
}

bool MainWindow::MoveShiB(Chessman *chess, int x, int y)
{
    bool res = false;
    if (abs(chess->getX() - x) == 1 && abs(chess->getY() - y) == 1 && x >= 3 &&
        x <= 5 && y <= 3) {
        res = true;
    }
    return res;
}

bool MainWindow::MoveChe(Chessman *chess, int x, int y)
{
    bool res = false;
    // 记录车路劲上的障碍物的数量。
    int c = 0;
    // 情况一,横向移动，判断车在移动时经过的棋子有多少个，若果大于1个那么就不移动。
    // 如果等于1个那么需要需要判断是否与车的角色相同，相同不移动，不同移动
    if (chess->getX() == x && chess->getY() != y) {
        int minY = 0, maxY = 0;
        if (y > chess->getY()) {
            minY = chess->getY();
            maxY = y;
        } else if (y < chess->getY()) {
            minY = y;
            maxY = chess->getY();
        }
        for (int i = minY; i <= maxY; i++) {
            Chessman *tempchess = getChess(x, i);
            if (tempchess != nullptr && chess->getY() != i) {
                c++;
            }
        }
    }
    // 情况二,纵向移动判断
    if (chess->getY() == y && chess->getX() != x) {
        int minX = 0, maxX = 0;
        if (x > chess->getX()) {
            minX = chess->getX();
            maxX = x;
        } else if (x < chess->getX()) {
            minX = x;
            maxX = chess->getX();
        }
        for (int i = minX; i <= maxX; i++) {
            Chessman *tempchess = getChess(i, y);
            if (tempchess != nullptr && chess->getX() != i) {
                c++;
            }
        }
    }
    if (c <= 1) {
        res = true;
    }
    return res;
}

bool MainWindow::MoveMa(Chessman *chess, int x, int y)
{
    bool res = false;
    if ((abs(chess->getX() - x) + abs(chess->getY() - y)) == 3) {
        res = true;
    } else {
        return false;
    }
    // 蹩马腿判断
    if (abs(chess->getX() - x) == 2) {
        if (x > chess->getX()) {
            Chessman *temp = getChess(chess->getX() + 1, chess->getY());
            if (temp != nullptr) {
                res = false;
            }
        } else {
            Chessman *temp = getChess(chess->getX() - 1, chess->getY());
            if (temp != nullptr) {
                res = false;
            }
        }
    } else if (abs(chess->getY() - y) == 2) {
        if (y > chess->getY()) {
            Chessman *temp = getChess(chess->getX(), chess->getY() + 1);
            if (temp != nullptr) {
                res = false;
            }
        } else {
            Chessman *temp = getChess(chess->getX(), chess->getY() - 1);
            if (temp != nullptr) {
                res = false;
            }
        }
    }

    return res;
}

bool MainWindow::MovePao(Chessman *chess, int x, int y)
{
    int res = false;
    int c = 0;
    if (chess->getX() == x && chess->getY() != y) {
        int minY = 0, maxY = 0;
        if (y > chess->getY()) {
            minY = chess->getY();
            maxY = y;
        } else if (y < chess->getY()) {
            minY = y;
            maxY = chess->getY();
        }
        for (int i = minY; i <= maxY; i++) {
            Chessman *tempchess = getChess(x, i);
            if (tempchess != nullptr && chess->getY() != i) {
                c++;
            }
        }
    }
    if (chess->getY() == y && chess->getX() != x) {
        int minX = 0, maxX = 0;
        if (x > chess->getX()) {
            minX = chess->getX();
            maxX = x;
        } else if (x < chess->getX()) {
            minX = x;
            maxX = chess->getX();
        }
        for (int i = minX; i <= maxX; i++) {
            Chessman *tempchess = getChess(i, y);
            if (tempchess != nullptr && chess->getX() != i) {
                c++;
            }
        }
    }
    if (c == 0) {
        res = true;
    } else if (c == 2) {
        res = true;
    }
    return res;
}

bool MainWindow::MoveJiangR(Chessman *chess, int x, int y)
{
    if (x >= 3 && x <= 5 && y >= 7) {
        if ((abs(chess->getX() - x) + abs(chess->getY() - y)) == 1) {
            return true;
        }
    }
    return false;
}

bool MainWindow::MoveJiangB(Chessman *chess, int x, int y)
{
    if (x >= 3 && x <= 5 && y <= 2) {
        if ((abs(chess->getX() - x) + abs(chess->getY() - y)) == 1) {
            return true;
        }
    }
    return false;
}

GameType MainWindow::gameOver()
{
    for (auto item : m_lstChess) {
        if (item->getChessType() == Jiang_B && !item->getLive()) {
            return Red_win;
        } else if (item->getChessType() == Jiang_R && !item->getLive()) {
            return Black_win;
        }
    }
    return running;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->setFixedSize(this->size());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = -1, y = -1;
    // 获取当前鼠标选中的坐标
    QPoint Coordinates = getChessboardCoordinates(event->x(), event->y());
    x = Coordinates.x();
    y = Coordinates.y();

    // 如果已经被选择那么就不处理
    if (this->getSelectedChess() != QPoint(-1, -1)) {
        // 如果选择相同颜色的棋子就切换选择的棋子
        for (auto item : m_lstChess) {
            if (m_Role == Red) {
                if (x != -1 && y != -1 && item->getX() == x &&
                    item->getY() == y && item->getChessType() <= Bing_R) {
                    selectChess(x, y);
                    return;
                }
            } else if (m_Role == Black) {
                if (x != -1 && y != -1 && item->getX() == x &&
                    item->getY() == y && item->getChessType() > Bing_R) {
                    selectChess(x, y);
                    return;
                }
            }
        }
        for (auto item : m_lstChess) {
            if (item->getSelectedStatus() && x != -1 && y != -1) {
                if (x != item->getX() || y != item->getY()) {
                    MoveChess(item, x, y);
                }
            }
        }
    } else {
        selectChess(x, y);
    }

    qInfo() << "x:" << x << ",y:" << y;
}
