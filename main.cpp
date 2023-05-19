#include <QCoreApplication>
#include <QtNetwork>/*
#include <QApplication>*/
#include "mainwindow.h"

#include <fstream>

//typedef std::function<void(QNetworkReply*)> ResponseCallback;

//class RequestHandler : public QObject
//{
//    Q_OBJECT

//public:
//    explicit RequestHandler(QObject* parent = nullptr) : QObject(parent) {}

//    void sendRequest(const QUrl& url, const ResponseCallback& callback)
//    {
//        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
//        QNetworkReply* reply = manager->get(QNetworkRequest(url));

//        // Connect the finished signal to a lambda function
//        connect(reply, &QNetworkReply::finished, this, [=]() {
//            callback(reply);
//        });
//    }
//};

bool handleServerResponse(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isNull()) {
            if (jsonDoc.isArray()) {
                QJsonArray jsonArray = jsonDoc.array();

                // Iterate over the JSON array
                for (const QJsonValue& value : jsonArray) {
                    if (value.isObject()) {
                        QJsonObject jsonObj = value.toObject();
                        // Access JSON data using jsonObj
                        // Example:
                        QJsonValue nameValue = jsonObj["firstName"];
                        if (nameValue.isString()) {
                            QString name = nameValue.toString();
                            qDebug() << "Name:" << name;
                        }
                        QJsonValue lastNameValue = jsonObj["lastName"];
                        if (nameValue.isString()) {
                            QString name = lastNameValue.toString();
                            qDebug() << "Last:" << name;
                        }
                        QJsonValue middleNameValue = jsonObj["middleName"];
                        if (nameValue.isString()) {
                            QString name = middleNameValue.toString();
                            qDebug() << "Middle:" << name;
                        }
                        QJsonValue academicValue = jsonObj["academicDepartment"];
                        if (academicValue.isArray())
                        {
                                QVector<QString> academics;
                                QJsonArray academic = academicValue.toArray();
                                for(auto it = academic.begin(); it!=academic.end(); ++it)
                                {
                                    if((*it).isString())
                                {
                                        academics.push_back((*it).toString());
                                }
                                }
                            qDebug() << "academic:" << academic;
                        }
                        //"degree": "д.ф.-м.н.",
                       // "rank": "профессор",
                         //        "photoLink": "https://iis.bsuir.by/api/v1/employees/photo/500434",
                           //                    "calendarId": "4t4b9qurekmm2nnb2tjjdcseq0@group.calendar.google.com",
                        QJsonValue degree = jsonObj["degree"];
                        if(degree.isString())
                        {
                            QString degreeP = degree.toString();
                            qDebug() << "Degree:" << degree;
                        }
                        QJsonValue rank = jsonObj["rank"];
                        if(rank.isString())
                        {
                            QString rankP = rank.toString();
                            qDebug() << "rank:" << rankP;
                        }
                        QJsonValue photo = jsonObj["photoLink"];
                        if(photo.isString())
                        {
                            QString photoP = photo.toString();
                            qDebug() << "PhotoLink:" << photoP;
                        }
                        QJsonValue calendarID = jsonObj["calendarId"];
                        if(photo.isString())
                        {
                            QString calendarIDP = calendarID.toString();
                            qDebug() << "Calendar ID:" << calendarIDP;
                        }
                        QJsonValue idValue = jsonObj["id"];
                        {
                            int id = idValue.toInt();
                            qDebug() << "Id:" << id;
                        }
                        //"urlId": "i-abramov",
//                        "fio": "Абрамов И. И. (профессор)"
                        QJsonValue urlId = jsonObj["urlId"];
                        if(urlId.isString())
                        {
                            QString urldP = urlId.toString();
                            qDebug() << "Url Id:" << urldP;
                        }
                        QJsonValue fio = jsonObj["fio"];
                        if(fio.isString())
                        {
                            QString fioP = fio.toString();
                            qDebug() << "Url Id:" << fioP;
                        }
                        qDebug() << "\n\n\n";
                    }
                }
            }
        }

        // Further processing or initiating another request...
    } else {
        // Error handling
        qDebug() << "Error:" << reply->errorString();
    }

    // Clean up
    reply->deleteLater();
    RequestHandler* handler = qobject_cast<RequestHandler*>(reply->parent());
    handler->ongoingRequests.removeOne(reply);
    if (handler->ongoingRequests.isEmpty()) {
        QCoreApplication::quit();
    }
}

//void handleServerResponse1(QNetworkReply* reply)
//{
//    if (reply->error() == QNetworkReply::NoError) {
//        QByteArray responseData = reply->readAll();

//        // Parse JSON response
//        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
//        if (!jsonDoc.isNull()) {
//            if (jsonDoc.isArray()) {
//                QJsonArray jsonArray = jsonDoc.array();
//                for (const QJsonValue& value : jsonArray) {
//                    if (value.isObject()) {
//                        QJsonObject jsonObj = value.toObject();
//                        QJsonValue idValue = jsonObj["id"];
//                        qDebug() << "Id:" << idValue.toInt();
//                        QJsonValue audName = jsonObj["name"];
//                        qDebug() << "Name:" << audName.toString();
//                        QJsonValue audType = jsonObj["auditoryType"].toObject();
//                        qDebug() << " Aud id:" << audType["id"].toInt() << " Aud name: " << audType["name"].toString()
//                                 << " Aud abbrev: " << audType["abbrev"].toString();
//                        QJsonValue buildingNumber = jsonObj["buildingNumber"].toObject();
//                        qDebug() << " Building id: " << buildingNumber["id"].toInt() << " Building name: " << buildingNumber["name"].toString();
//                        QJsonValue departmentType = jsonObj["department"].toObject();
//                        qDebug() << " id Department: " << departmentType["idDepartment"].toInt() << " Abbrev: " << departmentType["abbrev"].toString()
//                                 << " name: " << departmentType["name"].toString() << " nameAndAbbrev: " << departmentType["nameAndAbbrev"].toString();
//                    }
//                }
//            }
//        }
//    } else {
//        qDebug() << "Error:" << reply->errorString();
//    }
//    reply->deleteLater();
//    QCoreApplication::quit();
//}

//    void serverResponse()
//{

//    if (reply->error() == QNetworkReply::NoError) {
//        QByteArray responseData = reply->readAll();

//        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
//        if (!jsonDoc.isNull()) {
//            if (jsonDoc.isArray()) {
//                QJsonArray jsonArray = jsonDoc.array();
//                for (const QJsonValue& value : jsonArray) {
//                    if (value.isObject()) {
//                        QJsonObject jsonObj = value.toObject();
//                        QJsonValue idValue = jsonObj["id"];
//                        int id = idValue.toInt();
//                        qDebug() << "id:" << id;
//                        QJsonValue emploeyeeValue = jsonObj["employee"];
//                        if (emploeyeeValue.isString()) {
//                            QString emploeyeeValue = emploeyeeValue.toString();
//                            qDebug() << "emploeyee:" << emploeyeeValue;
//                        }
//                        QJsonValue content = jsonObj["content"];
//                        if (content.isString()) {
//                            QString content = content.toString();
//                            qDebug() << "content:" << content;
//                        }
//                        QJsonValue date = jsonObj["date"];
//                        if (date.isString()) {
//                            QString date = date.toString();
//                            qDebug() << "date:" << date;
//                        }
//                        QJsonArray employeeDepartments = jsonObj["employeeDepartments"];
//                        for(auto obj : employeeDepartments)
//                        {
//                            qDebug()<< obj << ", ";
//                        }
//                        QJsonObject studenetGroups = jsonObj["studentGroups"].toObject();
//                        for(auto obj : studenetGroups)
//                        {
//                            auto tmp = obj.toObject();
//                            qDebug()<<"id, "<<tmp["id"]<<" , name:" << tmp["name"];
//                        }

//                    }
//                }
//            }
//        }
//    } else {
//        qDebug() << "Error:" << reply->errorString();
//    }
////    reply->deleteLater();
//}

void kafedri(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isArray()) {
            QJsonArray jsonArray = jsonDoc.array();

            // Iterate over the JSON array
            for (const QJsonValue& value : jsonArray) {
                if (value.isObject()) {
                    QJsonObject jsonObj = value.toObject();
                    // Access JSON data using jsonObj
                    // Example:
                    QJsonValue id = jsonObj["id"];
                    if(id.isDouble()){
                        qDebug() << "Id: " << id;
                    }
                    QJsonValue nameValue = jsonObj["name"];
                    if (nameValue.isString()) {
                        QString name = nameValue.toString();
                        qDebug() << "Name:" << name;
                    }
                    QJsonValue abbrevKafedra = jsonObj["abbrev"];
                    if (abbrevKafedra.isString()) {
                        QString kafedra = abbrevKafedra.toString();
                        qDebug() << "Kaf: " << kafedra;
                    }
        }
    }
        }
    }
    }
}


void handleServerTeachersShedule(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isArray()) {
    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
                    QJsonObject jsonObj = value.toObject();
                    QJsonValue lastUpdateDate = jsonObj["lastUpdateDate"];
                    qDebug() << "lastUpdateDate: " << lastUpdateDate.toString();
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

void handleServerFaculties(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isArray()) {
    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
                    QJsonObject jsonObj = value.toObject();
                    QJsonValue facultyName = jsonObj["name"];
                    qDebug() << "Name: " << facultyName.toString();
                    QJsonValue abbrev = jsonObj["abbrev"];
                    qDebug() << "Abbrev: " << abbrev.toString();
                    out << abbrev.toString().toStdString() << '\n';
                    QJsonValue id = jsonObj["id"];
                    qDebug() << "Id: " << id.toInt();
                    out << facultyName.toInt() << '\n';
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


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    RequestHandler handler;
    QUrl url("https://iis.bsuir.by/api/v1/faculties");
    handler.sendRequest(url, handleServerFaculties);
    //handler.sendRequest(url, handleServerTeachersShedule);
    return a.exec();
}


//int main(int argc, char* argv[])
//{
////    QApplication a(argc, argv);
////    MainWindow w;
//    QCoreApplication a(argc, argv);

//    RequestHandler handler;
//    RequestHandler anotherHandler;


//    // Send the request and pass the callback function
//    QUrl urlemployees("https://iis.bsuir.by/api/v1/employees/all");
////    handler.sendRequest(urlemployees, handleServerResponse);

//    QUrl url("https://iis.bsuir.by/api/v1/departments");
////    handler.sendRequest(url, handleServerResponse1);


//    handler.sendRequest(url, kafedri);
//    anotherHandler.sendRequest(urlemployees, handleServerResponse);
//    // Start the event loop
//    return a.exec();
////    w.show();
////    return a.exec();
//}

#include "main.moc"
