QT          += opengl widgets

HEADERS     = bodies.h\
              widget.h \
              window.h \
              renderer.h
SOURCES     = bodies.cpp\
              main.cpp \
              widget.cpp \
              window.cpp \
              renderer.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
INSTALLS += target
