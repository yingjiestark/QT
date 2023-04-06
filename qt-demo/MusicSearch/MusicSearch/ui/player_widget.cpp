#include "player_widget.h"
#include <QStandardItemModel>
#include <QHeaderView>
PlayerWidget::PlayerWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrPlayerManger(new QMediaPlayer(this))
    , m_ptrTaleListView(new QTableView(this))
    , m_ptrLabMusicImage(new QLabel(this))
    , m_ptrLayoutView(new QHBoxLayout)
    , m_ptrBtnPreviousSong(new QPushButton(this))
    , m_ptrBtnStartOrPause(new QPushButton(this))
    , m_ptrBtnNextSong(new QPushButton(this))
    , m_ptrLabCurrentTime(new QLabel(this))
    , m_ptrSldPlayerProgress(new QSlider(this))
    , m_ptrLabTotalTime(new QLabel(this))
    , m_ptrLabVolume(new QLabel(this))
    , m_ptrSldVolume(new QSlider(this))
    , m_ptrLayoutPlayer(new QHBoxLayout)
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_ptrModel(new QStandardItemModel(this))
{
    initUI();
    initConnect();
    initData();
}

void PlayerWidget::initUI()
{
    m_ptrTaleListView->setMaximumWidth(400);
    m_ptrTaleListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ptrTaleListView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ptrTaleListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // m_ptrTaleListView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_ptrLayoutView->addWidget(m_ptrTaleListView);
    m_ptrLayoutView->addWidget(m_ptrLabMusicImage);
    m_ptrLayoutMain->addLayout(m_ptrLayoutView);

    m_ptrBtnPreviousSong->setText("上一曲");
    m_ptrLayoutPlayer->addWidget(m_ptrBtnPreviousSong);
    m_ptrBtnStartOrPause->setText("播放");
    m_ptrLayoutPlayer->addWidget(m_ptrBtnStartOrPause);
    m_ptrBtnNextSong->setText("下一曲");
    m_ptrLayoutPlayer->addWidget(m_ptrBtnNextSong);

    m_ptrSldPlayerProgress->setOrientation(Qt::Orientation::Horizontal);
    m_ptrLabCurrentTime->setText("00:00");
    m_ptrLayoutPlayer->addWidget(m_ptrLabCurrentTime);
    m_ptrLayoutPlayer->addWidget(m_ptrSldPlayerProgress);
    m_ptrLabTotalTime->setText("00:00");
    m_ptrLayoutPlayer->addWidget(m_ptrLabTotalTime);

    m_ptrSldVolume->setOrientation(Qt::Orientation::Horizontal);
    QPixmap volumeImage;
    volumeImage.load(QString(":/horn.png"));

    QPixmap scaledimg;
    scaledimg =
        volumeImage.scaled(m_ptrLabVolume->height(), m_ptrLabVolume->height());
    //    m_ptrLabVolume->setFixedSize(50, 50);
    m_ptrLabVolume->setPixmap(scaledimg);
    m_ptrLabVolume->setScaledContents(true);

    m_ptrLayoutPlayer->addWidget(m_ptrLabVolume);
    m_ptrLayoutPlayer->addWidget(m_ptrSldVolume);

    m_ptrLayoutMain->addLayout(m_ptrLayoutPlayer);
    setLayout(m_ptrLayoutMain);
}

void PlayerWidget::initConnect()
{
    connect(m_ptrBtnPreviousSong, &QPushButton::clicked, this,
            &PlayerWidget::slotPreviousSong);

    connect(m_ptrBtnStartOrPause, &QPushButton::clicked, this,
            &PlayerWidget::slotStartOrPause);

    connect(m_ptrBtnNextSong, &QPushButton::clicked, this,
            &PlayerWidget::slotNextSong);
    connect(m_ptrTaleListView, &QTableView::clicked, this,
            &PlayerWidget::slotTableClicked);

    connect(m_ptrPlayerManger, &QMediaPlayer::positionChanged, this,
            &PlayerWidget::slotPositionChanged);

    connect(m_ptrSldVolume, &QSlider::sliderMoved, this,
            &PlayerWidget::slotVolumeSliderMoved);
}

void PlayerWidget::initData()
{
    QList<AbsListLocal> list = DBManager::instance()->getList();
    int size = list.size();
    m_ptrModel->setColumnCount(3);
    m_ptrModel->setHeaderData(0, Qt::Horizontal, "音乐名称");
    m_ptrModel->setHeaderData(1, Qt::Horizontal, "演唱者");
    m_ptrModel->setHeaderData(2, Qt::Horizontal, "歌曲标号");
    int row = 0;
    for (int i = 0; i < size; i++) {
        m_ptrModel->setItem(row, 0, new QStandardItem(list.at(i).NAME));
        m_ptrModel->setItem(row, 1, new QStandardItem(list.at(i).ARTIST));
        m_ptrModel->setItem(row, 2, new QStandardItem(list.at(i).MUSICRID));
        row++;
    }
    m_ptrTaleListView->setModel(m_ptrModel);
}

void PlayerWidget::slotPreviousSong() {}

void PlayerWidget::slotStartOrPause()
{
    if (m_ptrPlayerManger->state() == QMediaPlayer::PlayingState) {
        m_ptrPlayerManger->pause();
        m_ptrBtnStartOrPause->setText("播放");
    } else {
        m_ptrPlayerManger->play();
        m_ptrBtnStartOrPause->setText("暂停");
    }
}

void PlayerWidget::slotNextSong() {}

void PlayerWidget::slotProgressSliderMoved(int postion) {}

void PlayerWidget::slotVolumeSliderMoved(int postion)
{
    m_ptrPlayerManger->setVolume(postion);
}

void PlayerWidget::slotTableClicked()
{
    int row = m_ptrTaleListView->currentIndex().row();
    QModelIndex index1 = m_ptrModel->index(row, 2);
    QString MUSICRID = m_ptrModel->data(index1).toString();
    qInfo() << "MUSICRID :" << MUSICRID;
    QList<AbsListLocal> info = DBManager::instance()->getInfoFromRId(MUSICRID);
    if (info.size() == 0) {
        return;
    }
    m_ptrPlayerManger->setMedia(QUrl::fromLocalFile(info.at(0).localPath));

    m_ptrPlayerManger->play();
    qint64 time = m_ptrPlayerManger->duration();
    qInfo() << "time:" << time;
    m_ptrSldVolume->setValue(m_ptrPlayerManger->volume());
    m_ptrBtnStartOrPause->setText("暂停");
}

void PlayerWidget::slotPositionChanged(int position)
{
    if (m_ptrPlayerManger->duration() != m_ptrSldPlayerProgress->maximum())

    {
        QString time =
            QString("%1").arg(int(m_ptrPlayerManger->duration() / (1000 * 60)),
                              2, 10, QChar('0'));

        time = time + ":" +
               QString("%1").arg(int(m_ptrPlayerManger->duration() / 1000) % 60,
                                 2, 10, QChar('0'));
        m_ptrLabTotalTime->setText(time);
        m_ptrSldPlayerProgress->setMaximum(m_ptrPlayerManger->duration());
    }
    if (position != 0) {
        QString ctime =
            QString("%1").arg(int(position / (1000 * 60)), 2, 10, QChar('0'));
        ctime = ctime + ":" +
                QString("%1").arg(int(position / 1000) % 60, 2, 10, QChar('0'));
        m_ptrLabCurrentTime->setText(ctime);
    }

    m_ptrSldPlayerProgress->setValue(position);
}

void PlayerWidget::slotInsertDownData(AbsListLocal info)
{
    qInfo() << "slotInsertDownData";
    qInfo() << "slotInsertDownData:" << info.NAME;
    int row = m_ptrModel->rowCount();
    m_ptrModel->setItem(row, 0, new QStandardItem(info.NAME));
    m_ptrModel->setItem(row, 1, new QStandardItem(info.ARTIST));
    m_ptrModel->setItem(row, 2, new QStandardItem(info.MUSICRID));
}
