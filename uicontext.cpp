#include "uicontext.h"

UiContext::UiContext()
{
    clear();
}

void UiContext::init(QQuickWindow *root, QQmlEngine *engine)
{
    this->root = root;
    this->engine = engine;
    this->component = new QQmlComponent(engine, "qrc:///bubble.qml");
}

void UiContext::clear()
{
    this->root = nullptr;
    this->engine = nullptr;
    this->component = nullptr;
    this->maxBubbles = 20;
    this->zoom = 1.0;
}
