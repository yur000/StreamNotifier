#ifndef NETWORKREQUESTS_H
#define NETWORKREQUESTS_H

#include <QObject>
#include <QtNetwork/QtNetwork>

class NetworkRequests : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *nam;
    QUrl url;
    QString usage;
    struct requestNode
    {
        QString usage;
        QUrl url;
    };
    QQueue<requestNode> *reguestQuenue;
    requestNode *reqNode;
    bool busy;
public:
    explicit NetworkRequests(QObject *parent = 0);
    void sendRequest(QUrl, QString);
    ~NetworkRequests();

signals:
    void ready(QByteArray, QString);
private slots:
    void checkState();
    void getAnswer(QNetworkReply*);

};

#endif // NETWORKREQUESTS_H
