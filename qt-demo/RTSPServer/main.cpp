#include "mainwindow.h"
#include <QApplication>
#include <QCameraInfo>
#include "live/V4l2H264DevUnicastServerMediaSubsession.h"
#include "live/V4l2H264DevMulticastServerMediaSubsession.h"
#include "live/AlsaAACDevUnicastServerMediaSubsession.h"
#include "live/AlsaAACDevMulticastServerMediaSubsession.h"

int main(int argc, char* argv[])
{
    QList<QCameraInfo> lists = QCameraInfo::availableCameras();
    foreach (auto item, lists) {
        qInfo() << item.description();
        qInfo() << item.deviceName();
    }

    int port = 8554;
    int videoWidth = 320;
    int videoHeight = 240;
    int videoFps = 15;
    int index = -1;
    std::string audioSamplingFmt("s16le");
    std::string deviceName;

    char c;

    if (argc == 1) {
        return 0;
    }

    while ((c = getopt(argc, argv, "i:p")) != -1) {
        switch (c) {
            case 'p':
                port = atoi(optarg);
                printf("port: %d\n", port);
                break;

            case 'i':
                index = atoi(optarg);
                printf("index: %d\n", port);
                break;
        }
    }
    if (-1 == index || index >= lists.size()) {
        printf("please select device index: %d\n", port);
        exit(-1);
    }
    deviceName = lists.at(index).deviceName().toStdString();
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

    RTSPServer* rtspServer = RTSPServer::createNew(*env, port);
    if (rtspServer == nullptr) {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        return -1;
    }

    ServerMediaSession* sms;

    sms = ServerMediaSession::createNew(*env, "live", "live rtsp server",
                                        "live rtsp server");

    if (!deviceName.empty())
        sms->addSubsession(V4l2H264DevUnicastServerMediaSubsession::createNew(
            *env, deviceName.c_str(), True, videoWidth, videoHeight, videoFps));

    rtspServer->addServerMediaSession(sms);

    char* url = rtspServer->rtspURL(sms);
    *env << "Play this stream using the URL \"" << url << "\"\n";
    delete[] url;

    env->taskScheduler().doEventLoop();

    return 0;
}
