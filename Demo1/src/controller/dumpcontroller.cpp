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

    QUrl urlRes("https://mts-aidocprocessing-case.olymp.innopolis.university");
    QUrl urlTok("https://mts-aidocprocessing-case.olymp.innopolis.university");
    QUrl urlDet("https://mts-aidocprocessing-case.olymp.innopolis.university");
    QUrl urlEmb("https://mts-aidocprocessing-case.olymp.innopolis.university");

    //Создание запроса к Api языковой модели
    QByteArray reqdata;
    //reqdata.append();
    QNetworkRequest req(urlRes);
    netMan->post(req,reqdata);

    response.setHeader("Content-Type", "json");
    //response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
    //response.setCookie(HttpCookie("secondCookie","world",600));

    //Создание Json для ответа на запрос фронта
    QByteArray body("{\"defalt\":\"False\"}");
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
