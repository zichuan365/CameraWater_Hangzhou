TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++0x
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    xmlreader.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    gpioset.cpp \
    XMLWriter.cpp \
    dcamera.cpp
HEADERS += \
    xmlreader.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    gpioset.h \
    XMLWriter.h \
    dcamera.h

#Daheng
INCLUDEPATH +=/home/nvidia/Galaxy_camera/inc
LIBS+=/usr/lib/libgxiapi.so

#opencv
INCLUDEPATH+=/usr/include/opencv
INCLUDEPATH+=/usr/include/opencv2
LIBS+= \
/usr/lib/libopencv_core.so.3.3.1 \
/usr/lib/libopencv_flann.so.3.3.1 \
/usr/lib/libopencv_highgui.so.3.3.1 \
/usr/lib/libopencv_imgcodecs.so.3.3.1 \
/usr/lib/libopencv_imgproc.so.3.3.1 \
/usr/lib/libopencv_calib3d.so.3.3.1 \
/usr/lib/aarch64-linux-gnu/libpthread.so
