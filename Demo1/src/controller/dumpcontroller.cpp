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
    QJsonDocument jsonResponse = QJsonDocument::fromJson(frontrequest);
    QJsonObject obj = jsonResponse.object();
    QString question = obj.value("content").toString();
    //Подключение к Api языковой модели
    QUrl urlRes("https://innoglobalhack-general.olymp.innopolis.university/v1/completions");
    QUrl urlDet("https://innoglobalhack-general.olymp.innopolis.university/detokenize");
    QUrl urlEmb("https://innoglobalhack-general.olymp.innopolis.university/v1/embeddings");
    QJsonObject ApiTokenize;
    QJsonObject Massege;
    QString role = "user";
    Massege.insert("role", role);
    Massege.insert("content", question);
    QJsonArray Messages;
    Messages.append(Massege);
    ApiTokenize.insert("model", "meta-llama/Llama-3.2-11B-Vision-Instruct");
    ApiTokenize.insert("add_special_tokens", true);
    ApiTokenize.insert("messages", Messages);

    QJsonDocument doc(ApiTokenize);
    QByteArray res = doc.toJson(QJsonDocument::Compact);
    netMan = new QNetworkAccessManager();
    QUrl urlTok("https://innoglobalhack-general.olymp.innopolis.university/tokenize");
    QNetworkRequest req(urlTok);
    req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    QByteArray result;
    QNetworkReply *rep = netMan->post(req,res);
    QObject::connect(rep, &QNetworkReply::finished, this, [=](){
        if(rep->error() == QNetworkReply::NoError){
            QString contents = QString::fromUtf8(rep->readAll());
            qDebug()<<rep->errorString();
            qDebug() << contents;
            return contents.toUtf8();
        }
        else{
            QString err = rep->errorString();
            qDebug() << err;
        }
        return rep->errorString().toUtf8();
        rep->deleteLater();
        });
    response.setHeader("Content-Type", "application/json");
    response.write(result,true);

    //response.write(body,true);
}
