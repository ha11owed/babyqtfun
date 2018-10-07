#pragma once

#include <QQuickItem>
#include <memory>
#include "uicontext.h"

class Effect
{
public:
    Effect(std::shared_ptr<UiContext> context);
    ~Effect();

    void key(QChar ch);

    void tick();

    bool isAlive() const;

private:
    void safeDelete();

    long _timeToLive;
    QPoint _position;
    QQuickItem* _item;
    std::shared_ptr<UiContext> _context;
};
