#ifndef STOCKEXCHANGE_H
#define STOCKEXCHANGE_H
#include <QList>


class Brocker;

class StockExchange
{
private:
    int sharesCount;
    QList<float> sharesPrices;
    QList<Brocker*> subscribers;
public:
    StockExchange(int sharesCount, float initialPrice);

    int getSharesCount() const;
    const QList<float>& getSharesPrices() const;
    void addSubscriber(Brocker* subscriber);

    void buy(int count, Brocker* brocker);
    void sell(int count, Brocker* brocker);

    void update();
};

class Brocker
{
private:
    int sharesCount = 0;
public:
    virtual void onUpdate(StockExchange* stock) = 0;
    int getSharesCount() const;
    void setSharesCount(int newSharesCount);
    virtual ~Brocker(){}
};

class Brocker1 : public Brocker
{
public:
    void onUpdate(StockExchange* stock) override;
    ~Brocker1() override {}
};

class Brocker2 : public Brocker
{
public:
    void onUpdate(StockExchange* stock) override;
    ~Brocker2() override {}
};

class Brocker3 : public Brocker
{
public:
    void onUpdate(StockExchange* stock) override;
    ~Brocker3() override {}
};



#endif // STOCKEXCHANGE_H
