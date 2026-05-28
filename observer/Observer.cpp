#include "Observer.h"

#include <algorithm>

void Subject::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    observers.erase(it);
}

void Subject::notify()
{
    for (auto& observer: observers)
        observer->onNotify();
}