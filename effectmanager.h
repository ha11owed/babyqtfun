#pragma once

#include <QObject>

#include <list>
#include <memory>
#include "effect.h"
#include "uicontext.h"

class EffectManager : public QObject
{
    Q_OBJECT

public:
    EffectManager();

    std::shared_ptr<UiContext> context();

public slots:
    void cppSlot(const QVariant &v);
    void tick();

private:
    std::shared_ptr<UiContext> _context;
    std::list<std::unique_ptr<Effect>> _effects;
};
