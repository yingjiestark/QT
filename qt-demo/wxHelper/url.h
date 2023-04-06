#ifndef URL_H
#define URL_H

/**
API_login: 'https://' + loginHost + '/cgi-bin/mmwebwx-bin/login',
API_synccheck: 'https://' + pushHost + '/cgi-bin/mmwebwx-bin/synccheck',
API_webwxdownloadmedia: 'https://' + fileHost +
'/cgi-bin/mmwebwx-bin/webwxgetmedia', API_webwxuploadmedia: 'https://' +
fileHost + '/cgi-bin/mmwebwx-bin/webwxuploadmedia',
API_webwxpreview:'/cgi-bin/mmwebwx-bin/webwxpreview',
API_webwxinit:"/cgi-bin/mmwebwx-bin/webwxinit?r="+~new Date(),
API_webwxgetcontact:"/cgi-bin/mmwebwx-bin/webwxgetcontact",
API_webwxsync:"/cgi-bin/mmwebwx-bin/webwxsync",
API_webwxbatchgetcontact:'/cgi-bin/mmwebwx-bin/webwxbatchgetcontact',
API_webwxgeticon:'/cgi-bin/mmwebwx-bin/webwxgeticon',
API_webwxsendmsg:'/cgi-bin/mmwebwx-bin/webwxsendmsg',
API_webwxsendmsgimg:'/cgi-bin/mmwebwx-bin/webwxsendmsgimg',
API_webwxsendmsgvedio:'/cgi-bin/mmwebwx-bin/webwxsendvideomsg',
API_webwxsendemoticon:'/cgi-bin/mmwebwx-bin/webwxsendemoticon',
API_webwxsendappmsg:'/cgi-bin/mmwebwx-bin/webwxsendappmsg',
API_webwxgetheadimg:'/cgi-bin/mmwebwx-bin/webwxgetheadimg',
API_webwxgetmsgimg:'/cgi-bin/mmwebwx-bin/webwxgetmsgimg',
API_webwxgetmedia:'/cgi-bin/mmwebwx-bin/webwxgetmedia',
API_webwxgetvideo:'/cgi-bin/mmwebwx-bin/webwxgetvideo',
API_webwxlogout:'/cgi-bin/mmwebwx-bin/webwxlogout',
API_webwxgetvoice:'/cgi-bin/mmwebwx-bin/webwxgetvoice',
API_webwxupdatechatroom:'/cgi-bin/mmwebwx-bin/webwxupdatechatroom',
API_webwxcreatechatroom:'/cgi-bin/mmwebwx-bin/webwxcreatechatroom',
API_webwxstatusnotify: '/cgi-bin/mmwebwx-bin/webwxstatusnotify',
API_webwxcheckurl: '/cgi-bin/mmwebwx-bin/webwxcheckurl',
API_webwxverifyuser: '/cgi-bin/mmwebwx-bin/webwxverifyuser',
API_webwxfeedback: '/cgi-bin/mmwebwx-bin/webwxsendfeedback',
API_webwxreport: '/cgi-bin/mmwebwx-bin/webwxstatreport',
API_webwxsearch: '/cgi-bin/mmwebwx-bin/webwxsearchcontact',
API_webwxoplog: '/cgi-bin/mmwebwx-bin/webwxoplog',
API_checkupload:'/cgi-bin/mmwebwx-bin/webwxcheckupload',
*/

extern const char kWebwxinit[];
// 请求联系人列表
extern const char kWebwxgetcontactURL[];

#endif  // URL_H
