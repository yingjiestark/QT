#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QList>

// 每一页搜索的数量
#define PAGE_NUM_STR 10

// 网络数据结构
typedef struct _AbsList {
    QString AARTIST;   // 歌手英文名字列表，以###分割
    QString ARTIST;    // 歌手中文名字列表，以&进行分割
    QString NAME;      // 歌名
    QString MUSICRID;  // 歌曲编码ID
    QString FORMATS;   // 音乐编码方式
    QString URL;
    QString IMAGE;
} AbsList;
Q_DECLARE_METATYPE(AbsList)

// 本地数据结构
typedef struct _AbsListLocal : _AbsList{
    void operator = (const AbsList &info)  {
        AARTIST = info.AARTIST;
        ARTIST = info.ARTIST;
        NAME = info.NAME;
        MUSICRID = info.MUSICRID;
        FORMATS = info.FORMATS;
        URL = info.URL;
        IMAGE = info.IMAGE;
    }
    QString id;         // 本地数据库对应的ID
    QString localPath;  // 本地音乐文件存储路径
    QString localImage;  // 本地音乐封面图存储路径.
}AbsListLocal;
Q_DECLARE_METATYPE(AbsListLocal)

typedef struct _SreachListInfo {
    int pn;     //
    int rn;     //
    int show;   //
    int total;  // 总数
    QList<AbsList> absList;
} SreachListInfo;

#endif  // COMMON_H
