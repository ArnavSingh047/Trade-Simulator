#include "WSClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

WSClient::WSClient(QObject *parent)
    : QObject(parent)
{
    connect(&webSocket, &QWebSocket::connected, this, &WSClient::onConnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &WSClient::onTextMessageReceived);
    connect(&webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred),
            this, &WSClient::onError);
}

void WSClient::connectToExchange(const QUrl &url)
{
    qDebug() << "Connecting to WebSocket:" << url;
    webSocket.open(url);
}

void WSClient::onConnected()
{
    qDebug() << "WebSocket connected";
}

void WSClient::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isObject()) {
        emit orderBookUpdated(doc.object());
    }
}

void WSClient::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    emit errorOccurred(webSocket.errorString());
}
