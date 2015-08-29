

#include "widget.h"
#include "window.h"

#include <QGridLayout>
#include <QTimer>

Window::Window()
{
    setWindowTitle("GravitySimulator");
    resize(618, 618);

    Widget *widget = new Widget(&renderer, this);
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(widget, 0, 0);
    setLayout(layout);

}
