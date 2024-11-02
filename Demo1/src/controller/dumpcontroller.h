/**
  @file
  @author Stefan Frings
*/

#ifndef DUMPCONTROLLER_H
#define DUMPCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "apiwork.h"
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

using namespace stefanfrings;

/**
  This controller dumps the received HTTP request in the response.
*/

class DumpController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(DumpController)
private:
    QNetworkAccessManager *netMan;
private slots:
    void onResult(QNetworkReply *);
public:

    /** Constructor */
    DumpController();
    // new comment

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};



#endif // DUMPCONTROLLER_H
