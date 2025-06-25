#include "SimulatorUI.h"
#include "models/SlippageModel.h"
#include "models/AlmgrenChriss.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QElapsedTimer>
#include <cmath>

SimulatorUI::SimulatorUI(QWidget *parent)
    : QMainWindow(parent), wsClient(new WSClient(this))
{
    QWidget *central = new QWidget;
    setCentralWidget(central);

    // Input widgets
    assetInput = new QLineEdit("BTC-USDT-SWAP");
    orderTypeInput = new QComboBox;
    orderTypeInput->addItem("Market");
    quantityInput = new QLineEdit("100");
    volatilityInput = new QLineEdit("0.05");
    feeTierInput = new QLineEdit("0.001");
    startButton = new QPushButton("Start Simulation");

    QFormLayout *inputLayout = new QFormLayout;
    inputLayout->addRow("Exchange:", new QLabel("OKX"));
    inputLayout->addRow("Asset:", assetInput);
    inputLayout->addRow("Order Type:", orderTypeInput);
    inputLayout->addRow("Quantity (USD):", quantityInput);
    inputLayout->addRow("Volatility:", volatilityInput);
    inputLayout->addRow("Fee Tier:", feeTierInput);
    inputLayout->addRow(startButton);

    // Output widgets
    slippageLabel   = new QLabel("-");
    feesLabel       = new QLabel("-");
    impactLabel     = new QLabel("-");
    netCostLabel    = new QLabel("-");
    makerTakerLabel = new QLabel("-");
    latencyLabel    = new QLabel("-");

    QFormLayout *outputLayout = new QFormLayout;
    outputLayout->addRow("Expected Slippage:", slippageLabel);
    outputLayout->addRow("Expected Fees:", feesLabel);
    outputLayout->addRow("Market Impact:", impactLabel);
    outputLayout->addRow("Net Cost:", netCostLabel);
    outputLayout->addRow("Maker/Taker Ratio:", makerTakerLabel);
    outputLayout->addRow("Latency (ms):", latencyLabel);

    // Combine
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(outputLayout);
    central->setLayout(mainLayout);

    // WebSocket signals
    connect(wsClient, &WSClient::orderBookUpdated, this, &SimulatorUI::handleOrderBookUpdate);
    connect(wsClient, &WSClient::errorOccurred, this, &SimulatorUI::handleError);
    connect(startButton, &QPushButton::clicked, [=]() {
        QUrl url(QStringLiteral("wss://ws.gomarket-cpp.goquant.io/ws/l2-orderbook/okx/") + assetInput->text());
        wsClient->connectToExchange(url);
    });
}

void SimulatorUI::handleOrderBookUpdate(const QJsonObject &data)
{
    static QElapsedTimer timer;
    static bool first = true;
    if (first) {
        timer.start();
        first = false;
    } else {
        qint64 elapsed = timer.restart();
        latencyLabel->setText(QString::number(elapsed));
    }

    auto bids = data["bids"].toArray();
    auto asks = data["asks"].toArray();
    if (bids.isEmpty() || asks.isEmpty()) return;

    double bestBid = bids[0].toArray()[0].toString().toDouble();
    double bestAsk = asks[0].toArray()[0].toString().toDouble();
    double midPrice = (bestBid + bestAsk) / 2.0;

    double qty  = quantityInput->text().toDouble();
    double vol  = volatilityInput->text().toDouble();
    double fee  = feeTierInput->text().toDouble();

    double slippage = SlippageModel::estimateSlippage(qty, midPrice);
    AlmgrenChriss impactModel(vol, 5000);
    double impact = impactModel.calculate_impact(qty);
    double fees   = fee * qty;
    double net    = slippage + impact + fees;

    slippageLabel->setText(QString::number(slippage, 'f', 2));
    impactLabel->setText(QString::number(impact, 'f', 2));
    feesLabel->setText(QString::number(fees, 'f', 2));
    netCostLabel->setText(QString::number(net, 'f', 2));
    makerTakerLabel->setText("60% Maker / 40% Taker");
}

void SimulatorUI::handleError(const QString &error)
{
    qDebug() << "WebSocket error:" << error;
}
