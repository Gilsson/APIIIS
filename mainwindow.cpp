#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QCoreApplication>
#include <QtNetwork>

QString items;
void MainWindow::handleServerResponse2(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();

        // Parse JSON response
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isArray()) {
                QJsonArray jsonArray = jsonDoc.array();
                for (const QJsonValue& value : jsonArray) {
                    if (value.isObject()) {
                        QJsonObject jsonObj = value.toObject();
                        QJsonValue idValue = jsonObj["id"];
                        qDebug() << "Id:" << idValue.toInt();
                        QJsonValue audName = jsonObj["name"];
                        qDebug() << "Name:" << audName.toString();
                        items.append(audName.toString());
                        QJsonValue audType = jsonObj["auditoryType"].toObject();
                        qDebug() << " Aud id:" << audType["id"].toInt() << " Aud name: " << audType["name"].toString()
                                 << " Aud abbrev: " << audType["abbrev"].toString();
                        QJsonValue buildingNumber = jsonObj["buildingNumber"].toObject();
                        qDebug() << " Building id: " << buildingNumber["id"].toInt() << " Building name: " << buildingNumber["name"].toString();
                        QJsonValue departmentType = jsonObj["department"].toObject();
                        qDebug() << " id Department: " << departmentType["idDepartment"].toInt() << " Abbrev: " << departmentType["abbrev"].toString()
                                 << " name: " << departmentType["name"].toString() << " nameAndAbbrev: " << departmentType["nameAndAbbrev"].toString();
                    }
                }
            }
        }
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
    QCoreApplication::quit();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{/*
    int currentId = ui->comboBox->currentIndex();
    qDebug() << currentId;
    RequestHandler handler;
    QString item = items;
    ui->textEdit->insertPlainText(item);
    switch(currentId)
    {
    case 0:
        QUrl url("https://iis.bsuir.by/api/v1/auditories");

        handler.sendRequest(url, handleServerResponse2);
        break;
    }*/
}

