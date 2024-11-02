#include "apiwork.h"

APIWork::APIWork()
{
    this->Data.setFileName(QDir::rootPath()+"GlobalHack/Demo1/etc/docroot/data.json");
}

QByteArray APIWork::Algorithm(QJsonObject &question){
    //QJsonObject res;
    QString val;
    Data.open(QIODevice::ReadOnly|QIODevice::Text);
    val=Data.readAll();
    QByteArray res = val.toUtf8();
    Data.close();
    //res = QJsonDocument::fromJson(val.toUtf8()).object();
    return res;
}
