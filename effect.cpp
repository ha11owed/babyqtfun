#include "effect.h"
#include <QRandomGenerator>
#include <QQmlContext>

const static int MaxTimeToLive = 100;

Effect::Effect(std::shared_ptr<UiContext> context)
{
    _timeToLive = 0;
    _position = QPoint(0, 0);
    _context = context;
    _item = nullptr;
}

Effect::~Effect()
{
    safeDelete();
}

void Effect::key(QChar ch)
{
    _timeToLive = MaxTimeToLive;

    QObject *obj = _context->component->create();
    QQuickItem *item = qobject_cast<QQuickItem*>(obj);

    int x = QRandomGenerator::global()->bounded(10,  _context->root->width() - 10);
    int y = QRandomGenerator::global()->bounded(10,  _context->root->height() - 10);
    item->setPosition(QPointF(x, y));
    item->setParentItem(_context->root->contentItem());
    item->setVisible(true);

    qreal scale = _context->zoom * (1.0 + QRandomGenerator::global()->bounded(0.7));
    item->setScale(scale);

    safeDelete();
    _item = item;
}

void Effect::tick()
{
    if(_timeToLive < 0)
    {
        return;
    }

    _timeToLive--;
    if(_timeToLive <= 0)
    {
        safeDelete();
    }

    if(_item != nullptr)
    {
        float r = _context->zoom * ((0.7 * MaxTimeToLive + _timeToLive) / MaxTimeToLive);
        if(r < _item->scale())
        {
            _item->setScale(r);
        }

        int maxx = _context->root->width();
        int maxy = _context->root->height();
        int dx = (int) QRandomGenerator::global()->bounded(0.001 * maxx);
        int dy = (int) QRandomGenerator::global()->bounded(0.001 * maxy);
        int newX = _item->x() + dx;
        int newY = _item->y() + dy;
        if (newX < 0 || newX >= maxx)
        {
            newX = _item->x();
        }
        if (newY < 0 || newY >= maxy)
        {
            newY = _item->y();
        }

        _item->setPosition(QPointF(newX, newY));
    }
}

bool Effect::isAlive() const
{
    return _timeToLive > 0;
}

void Effect::safeDelete()
{
    if(_item != nullptr)
    {
        delete _item;
        _item = nullptr;
    }
}
