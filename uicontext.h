#pragma once

#include <QQuickWindow>
#include <QQmlComponent>

class UiContext
{
public:
    UiContext();

    void init(QQuickWindow * root, QQmlEngine *engine);

    void clear();

public:
    QQuickWindow *root;
    QQmlEngine *engine;
    QQmlComponent *component;

    int maxBubbles;
    float zoom;
};
