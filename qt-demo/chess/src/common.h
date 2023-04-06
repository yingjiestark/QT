#ifndef COMMON_H
#define COMMON_H
enum ChessType  // 棋子类型
{ NullChess,    // 没有棋子
  Che_R,        // 车 - 红色
  Ma_R,         // 马 - 红色
  Xiang_R,      // 象 - 红色
  Shi_R,        // 士 - 红色
  Jiang_R,      // 将 - 红色
  Pao_R,        // 炮 - 红色
  Bing_R,       // 兵 - 红色
  Che_B,        // 车 - 黑色
  Ma_B,         // 马 - 黑色
  Xiang_B,      // 象 - 黑色
  Shi_B,        // 士 - 黑色
  Jiang_B,      // 将 - 黑色
  Pao_B,        // 炮 - 黑色
  Bing_B        // 兵 - 黑色
};
enum GameType { running, Red_win, Black_win };
enum RoleType  // 角色类型:红色先行
{ Red,
  Black };
extern int g_top;              // 棋盘的左上角X轴的启时坐标
extern int g_left;             // 棋盘的左上角Y轴的启时坐标
extern int g_chess_man_width;  // 每一个棋子的宽度
extern int g_cell_width;       // 每一个象棋方格的宽度
extern int g_game_width;       // 游戏界面的宽度
extern int maps[10][9];
#endif  // COMMON_H
