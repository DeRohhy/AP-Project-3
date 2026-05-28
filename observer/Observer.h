#pragma once

#include <vector>

class Observer
{
public:
    virtual ~Observer() {}

    virtual void onNotify() = 0;
};

class Subject
{
public:
    Subject() {}

    virtual ~Subject() {}

    virtual void addObserver(Observer* observer);

    virtual void removeObserver(Observer* observer);

    virtual void notify();
private:
    std::vector<Observer*> observers;
};