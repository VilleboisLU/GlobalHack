/**
  @file
  @author Stefan Frings
*/

#include "dumpcontroller.h"
#include <QVariant>
#include <QDateTime>
#include <QThread>

DumpController::DumpController()
{}

void DumpController::service(HttpRequest& request, HttpResponse& response)
{
    //Получение запроса от front
    QByteArray req = request.getBody();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(req);
    QJsonObject obj = jsonResponse.object();



    //Обращение к API
    netMan = new QNetworkAccessManager(this);
    QObject::connect(netMan, &QNetworkAccessManager::finished, this, &DumpController::onResult);

    QUrl UrlResult("https://innoglobalhack-general.olymp.innopolis.university/v1/completions");
    QUrl UrlTokenize("https://innoglobalhack-general.olymp.innopolis.university/tockenize");
    QUrl UrlDetokenize("https://innoglobalhack-general.olymp.innopolis.university/detockenize");
    QUrl UrlEmbeddings("https://innoglobalhack-general.olymp.innopolis.university/embeddings");

    QNetworkRequest requestAPI(UrlResult);

    netMan->post(requestAPI, req);

    //Ответ на front
    QByteArray body;

    response.write(body,true);
}

void DumpController::onResult(QNetworkReply *repl){
    if(repl->error() == QNetworkReply::NoError){
            QByteArray result = repl->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
            QJsonObject obj = jsonResponse.object();

            //Парсинг ответа API
    }
        repl->deleteLater();
}
