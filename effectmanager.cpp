#include "effectmanager.h"
#include <QVariant>

EffectManager::EffectManager()
{
    _context = std::make_shared<UiContext>();
}

std::shared_ptr<UiContext> EffectManager::context()
{
    return _context;
}

void EffectManager::cppSlot(const QVariant &v)
{
    QChar ch = v.toChar();

    if(_effects.size() >= _context->maxBubbles)
    {
        _effects.pop_front();
    }
    std::unique_ptr<Effect> effect = std::make_unique<Effect>(_context);
    effect->key(ch);

    _effects.push_back(std::move(effect));
}

void EffectManager::tick()
{
    _effects.remove_if([](std::unique_ptr<Effect>& e) { return !e->isAlive(); });
    for(auto& effect : _effects)
    {
        effect->tick();
    }
}
