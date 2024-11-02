#ifndef APIWORK_H
#define APIWORK_H
#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QUrlQuery>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

class APIWork
{
private:
    QFile Data;

public:
    APIWork();
    QByteArray Algorithm(QJsonObject&);
};


#endif // APIWORK_H
