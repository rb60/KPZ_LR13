#include "stockdrawer.h"
#include <QPainter>
#include <QPaintEvent>
#include <algorithm>

StockExchange *StockDrawer::getStock() const
{
    return stock;
}

void StockDrawer::setStock(StockExchange *newStock)
{
    stock = newStock;
}

int StockDrawer::getPriceCount() const
{
    return priceCount;
}

int StockDrawer::getPriceDivider() const
{
    return priceDivider;
}

void StockDrawer::setPriceDivider(int newPriceDivider)
{
    priceDivider = newPriceDivider;
}

int StockDrawer::getFontSize() const
{
    return fontSize;
}

void StockDrawer::setFontSize(int newFontSize)
{
    fontSize = newFontSize;
}

StockDrawer::StockDrawer(QWidget *parent)
    : QWidget{parent}
{}

void StockDrawer::paintEvent(QPaintEvent *event)
{
    if(stock == nullptr)
    {
        return;
    }

    QList<float> prices;
    if(stock->getSharesPrices().size() < priceCount)
    {
        prices = stock->getSharesPrices();
    }
    else
    {
        prices = stock->getSharesPrices().last(priceCount);
    }

    if(prices.size() == 0)
    {
        return;
    }

    float max = *(std::max_element(prices.begin(), prices.end()));

    int horizontalInterval = event->rect().width() / priceCount;
    int verticalInterval = event->rect().height() / priceDivider;
    float verticalMultiply = ((float)event->rect().height()) / max;
    int verticalDividerStep = max /  priceDivider;


    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));

    for(int i = 0; i < priceCount; i++)
    {
        p.drawLine(i * horizontalInterval + horizontalInterval / 2, 0, i * horizontalInterval + horizontalInterval / 2, event->rect().height());
    }

    for(int i = 1; i < priceDivider; i++)
    {
        p.drawLine(0, i * verticalInterval, event->rect().width(), i * verticalInterval);
    }


    p.setPen(QPen(Qt::green, 4));
    QLine line(QPoint(0 + horizontalInterval / 2, event->rect().height() - prices[0] * verticalMultiply),QPoint(0,0));
    for(int i = 1; i < prices.size(); i++)
    {
        line.setP2(QPoint(line.p1().x() + horizontalInterval, event->rect().height() - prices[i] * verticalMultiply));
        p.drawLine(line);
        line.setP1(line.p2());
    }


    p.setPen(QPen(Qt::black, 1));
    QFont font("Comic Sans MS");
    font.setPixelSize(fontSize);
    p.setFont(font);

    float price = 0;
    for(int i = 0; i < priceDivider; i++, price += verticalDividerStep)
    {
        p.drawText(0, event->rect().height() - (i * verticalInterval + fontSize), QString::number(price));
    }

    p.end();
}
