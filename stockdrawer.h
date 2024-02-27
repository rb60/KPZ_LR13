#ifndef STOCKDRAWER_H
#define STOCKDRAWER_H

#include <QWidget>
#include "stockexchange.h"

class StockDrawer : public QWidget
{
    Q_OBJECT
private:
    StockExchange *stock = nullptr;
    int priceCount = 10;
    int priceDivider = 10;
    int fontSize = 10;

public:
    explicit StockDrawer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

    StockExchange *getStock() const;
    void setStock(StockExchange *newStock);

    int getPriceCount() const;
    void setPriceCount(int newPriceCount);

    int getPriceDivider() const;
    void setPriceDivider(int newPriceDivider);

    int getFontSize() const;
    void setFontSize(int newFontSize);

signals:
};

#endif // STOCKDRAWER_H
