#include "stockexchange.h"

int StockExchange::getSharesCount() const
{
    return sharesCount;
}

const QList<float>& StockExchange::getSharesPrices() const
{
    return sharesPrices;
}

void StockExchange::addSubscriber(Brocker *subscriber)
{
    subscribers.push_back(subscriber);
}

void StockExchange::buy(int count, Brocker* brocker)
{
    if(brocker == nullptr)
    {
        return;
    }


    if(sharesCount >= count)
    {
        sharesCount -= count;
        brocker->setSharesCount(brocker->getSharesCount() + count);
    }

}

void StockExchange::sell(int count, Brocker* brocker)
{
    if(brocker == nullptr)
    {
        return;
    }

    if(brocker->getSharesCount() >= count)
    {
        sharesCount += count;
        brocker->setSharesCount(brocker->getSharesCount() - count);
    }

}

void StockExchange::update()
{
    int startCount = sharesCount;
    for(int i = 0; i < subscribers.size(); i++)
    {
        subscribers[i]->onUpdate(this);
    }
    int endCount = sharesCount;
    float change = ((float)startCount) / ((float)endCount);
    sharesPrices.push_back(sharesPrices.back() * change);
}

StockExchange::StockExchange(int sharesCount, float initialPrice) : sharesCount(sharesCount)
{
    sharesPrices.push_back(initialPrice);
}

int Brocker::getSharesCount() const
{
    return sharesCount;
}

void Brocker::setSharesCount(int newSharesCount)
{
    sharesCount = newSharesCount;
}

void Brocker1::onUpdate(StockExchange *stock)
{
    if(stock->getSharesPrices().size() < 3)
    {
        return;
    }

    QList<float> prices = stock->getSharesPrices().last(3);
    if(prices[0] > prices[1] && prices[1] < prices[2])
    {
        stock->buy(12, this);
    }

    if(prices[0] < prices[1] && prices[1] < prices[2])
    {
        stock->sell(3, this);
    }
}

void Brocker2::onUpdate(StockExchange *stock)
{
    if(stock->getSharesPrices().size() < 3)
    {
        return;
    }

    QList<float> prices = stock->getSharesPrices().last(3);
    if(prices[0] > prices[1] && prices[1] > prices[2])
    {
        stock->buy(3, this);
    }

    if(prices[0] < prices[1] && prices[1] > prices[2])
    {
        stock->sell(15, this);
    }
}

void Brocker3::onUpdate(StockExchange *stock)
{
    if(rand() % 2)
    {
        stock->buy(rand() % 7 + 1, this);
    }
    else
    {
        stock->sell(rand() % 7 + 1, this);
    }
}
