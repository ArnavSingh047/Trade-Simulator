#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonObject>

class WSClient : public QObject
{
    Q_OBJECT

public:
    explicit WSClient(QObject *parent = nullptr);
    void connectToExchange(const QUrl &url);

signals:
    void orderBookUpdated(const QJsonObject &data);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket webSocket;
};

#endif // WSCLIENT_H
