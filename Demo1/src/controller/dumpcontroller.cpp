/**
  @file
  @author Stefan Frings
*/

#include "dumpcontroller.h"
#include <QVariant>
#include <QDateTime>
#include <QThread>
#include <QCoreApplication>


DumpController::DumpController()
{}

void DumpController::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray frontrequest = request.getBody();
    //response.write(frontrequest,true);
    //Подключение к Api языковой модели
    netMan = new QNetworkAccessManager(this);
    QObject::connect(netMan, &QNetworkAccessManager::finished, this, &DumpController::onResult);

    QUrl urlRes("https://innoglobalhack-general.olymp.innopolis.university/v1/completions");
    QUrl urlTok("https://innoglobalhack-general.olymp.innopolis.university/tokenize");
    QUrl urlDet("https://innoglobalhack-general.olymp.innopolis.university/detokenize");
    QUrl urlEmb("https://innoglobalhack-general.olymp.innopolis.university/v1/embeddings");

    //Создание запроса к Api языковой модели
    QByteArray reqdata;
    //reqdata.append();
    QNetworkRequest req(urlRes);
    netMan->post(req,reqdata);

    QJsonObject val;
    APIWork api;
    QByteArray body;
    body = api.Algorithm(val);


    response.setHeader("Content-Type", "json");
    //response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
    //response.setCookie(HttpCookie("secondCookie","world",600));

    //Создание Json для ответа на запрос фронта

    response.write(body,true);
}

void DumpController::onResult(QNetworkReply *repl){
    if(repl->error() == QNetworkReply::NoError){

            QByteArray result = repl->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
            QJsonObject obj = jsonResponse.object();
            //qDebug() << obj;
    }
}
