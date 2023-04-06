#ifndef USERINFO_H
#define USERINFO_H
#include <QString>
// xml格式解析
struct userTokenInfo {
    QString skey;
    QString wxsid;
    QString wxuin;
    QString pass_ticket;
    QString isgrayscale;
};

struct xmlErr{
    xmlErr(){
        code = 0;
        message ="";
    }
  int code;
  QString message;

};
// json格式解析.
struct friendsInfo {
    QString Uin;
    QString UserName;  // 唯一标识
    QString NickName;
    qreal AttrStatus;
    QString PYInitial;
    QString PYQuanPin;
    QString RemarkPYInitial;
    QString RemarkPYQuanPin;
    QString MemberStatus;
    QString DisplayName;
    QString KeyWord;
};
#endif  // USERINFO_H
