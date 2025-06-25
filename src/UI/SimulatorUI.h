#ifndef SIMULATORUI_H
#define SIMULATORUI_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QElapsedTimer>
#include "websocket/WSClient.h"

class SimulatorUI : public QMainWindow
{
    Q_OBJECT

public:
    SimulatorUI(QWidget *parent = nullptr);

private slots:
    void handleOrderBookUpdate(const QJsonObject &data);
    void handleError(const QString &error);

private:
    WSClient *wsClient;

    QLineEdit *assetInput;
    QComboBox  *orderTypeInput;
    QLineEdit *quantityInput;
    QLineEdit *volatilityInput;
    QLineEdit *feeTierInput;

    QLabel *slippageLabel;
    QLabel *feesLabel;
    QLabel *impactLabel;
    QLabel *netCostLabel;
    QLabel *makerTakerLabel;
    QLabel *latencyLabel;

    QPushButton *startButton;
};

#endif // SIMULATORUI_H
