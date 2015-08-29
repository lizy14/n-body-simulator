
#ifndef WINDOW_H
#define WINDOW_H

#include "renderer.h"

#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    Renderer renderer;
};

#endif
