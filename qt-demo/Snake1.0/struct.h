#ifndef STRUCT_H
#define STRUCT_H
enum MoveDirection {
    moveRight,  // 向右移动
    moveLeft,   // 向左移动
    moveTop,    // 向上移动
    moveBottom  // 向下移动

};

enum GameStatus {
    gameInit,
    gameStart,
    gameOver

};

struct Block {
    int x;
    int y;
};
struct SnakeBoy : Block {
};
struct Food : Block {
};
#endif  // STRUCT_H
