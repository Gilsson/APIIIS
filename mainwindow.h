#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef std::function<void(QNetworkReply*)> ResponseCallback;

class RequestHandler : public QObject
{
    Q_OBJECT

public:
    explicit RequestHandler(QObject* parent = nullptr) : QObject(parent) {}

    void sendRequest(const QUrl& url, const ResponseCallback& callback)
    {
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkReply* reply = manager->get(QNetworkRequest(url));

        // Connect the finished signal to a lambda function
        connect(reply, &QNetworkReply::finished, this, [=]() {
            callback(reply);
        });

        // Add the reply to the ongoingRequests list
        ongoingRequests.append(reply);
    }
public:
    QList<QNetworkReply*> ongoingRequests;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    static void handleServerResponse2(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
