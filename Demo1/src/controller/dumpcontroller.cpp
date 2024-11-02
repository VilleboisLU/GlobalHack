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
    ApiTokenize.insert("add_special_tokens", true);
    ApiTokenize.insert("inputs", question);
    ApiTokenize.insert("prompt_name", QJsonValue::Null);


    QJsonDocument doc(ApiTokenize);
    QByteArray res = doc.toJson();
    //response.setHeader("Content-Type", "application/json");
    //response.write(res,true);
    QEventLoop eventLoop;
    netMan = new QNetworkAccessManager();
    QObject::connect(netMan, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setProtocol(QSsl::TlsV1_0);
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyPeer);

    QFile ca("RootCA.crt");
    if (ca.open(QIODevice::ReadOnly))
    {
      QSslCertificate cert = QSslCertificate(&ca);
      QList <QSslCertificate> caList;
      caList.append(cert);
      sslConfig.setCaCertificates(caList);
    }

    QNetworkRequest req;
    req.setUrl(QUrl( QString("https://mts-aidocprocessing-case-embedder.olymp.innopolis.university/tokenize") ));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setSslConfiguration(sslConfig);

    QNetworkReply *reply = netMan->post(req, res);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        result = reply->readAll();
    }

    response.setHeader("Content-Type", "application/json");
    response.write(result,true);


}
