#ifndef PLAYER_WIDGET_H
#define PLAYER_WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlayer>
#include "db/db_manager.h"
class QStandardItemModel;
/**
 * @brief 音乐播放界面
 */
class PlayerWidget : public QWidget {
    Q_OBJECT
   public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    void initUI();
    void initConnect();
    void initData();

   private:
    QMediaPlayer *m_ptrPlayerManger;

    QTableView *m_ptrTaleListView;  // 音乐列表
    QLabel *m_ptrLabMusicImage;     // 音乐封面
    QHBoxLayout *m_ptrLayoutView;   // 展示音乐列表以及音乐封面。

    QPushButton *m_ptrBtnPreviousSong;  // 上一曲
    QPushButton *m_ptrBtnStartOrPause;  // 开始或暂停
    QPushButton *m_ptrBtnNextSong;      // 下一曲
    QLabel *m_ptrLabCurrentTime;        // 当前音乐播放时间。
    QSlider *m_ptrSldPlayerProgress;    // 播放进度
    QLabel *m_ptrLabTotalTime;          // 当前音乐总时间。
    QLabel *m_ptrLabVolume;             // 音量大小调节
    QSlider *m_ptrSldVolume;            // 音量大小调节
    QHBoxLayout *m_ptrLayoutPlayer;     // 展示音乐播放页面。
    QVBoxLayout *m_ptrLayoutMain;       // 主界面
    QStandardItemModel *m_ptrModel;
   signals:

   public slots:

    void slotPreviousSong();
    void slotStartOrPause();
    void slotNextSong();
    void slotProgressSliderMoved(int position);
    void slotVolumeSliderMoved(int position);
    void slotTableClicked();
    void slotPositionChanged(int position);
    void slotInsertDownData(AbsListLocal info);
};

#endif  // PLAYER_WIDGET_H
