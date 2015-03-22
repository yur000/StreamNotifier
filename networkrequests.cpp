#include "networkrequests.h"


NetworkRequests::NetworkRequests(QObject *parent) :
    QObject(parent)
{
    reguestQuenue = new QQueue<requestNode>;
    busy = false;
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)), SLOT(getAnswer(QNetworkReply*)));
    connect(this, SIGNAL(ready(QByteArray,QString)), SLOT(checkState()));
}

void NetworkRequests::sendRequest(QUrl url_in)
{
    qDebug() << "in net";
    if(busy)
    {
        reqNode = new requestNode;
        reqNode->url = url_in;
        reguestQuenue->enqueue(*reqNode);
    }
    else
    {
        url = url_in;
        busy = true;
        QNetworkRequest request;
        request.setUrl(url);
        //connect(this, SIGNAL(ready(QString, QString)), nam, SLOT(deleteLater()));
        nam->get(request);
    }
}

void NetworkRequests::getAnswer(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError) \
    {
        QByteArray bytes = reply->readAll();
        //QString str(bytes);
        //qDebug() << str;
        busy = false;
        emit ready(bytes);
    }
    else
    {
        qWarning() << "Some problem with inet, saving state...";
        //reply->abort();
        reqNode = new requestNode;
        reqNode->url = url;
        reguestQuenue->enqueue(*reqNode);
        busy = false;
        QTimer::singleShot(2000, this, SLOT(checkState()));
    }
    reply->deleteLater();
    reply = 0;
}

void NetworkRequests::checkState()
{
    if(!reguestQuenue->isEmpty())
    {
        if(!busy)
        {
            requestNode tmpNode = reguestQuenue->dequeue();
            sendRequest(tmpNode.url, tmpNode.usage);
        }

    }
}

NetworkRequests::~NetworkRequests()
{
    delete reguestQuenue;
    nam->deleteLater();
}
