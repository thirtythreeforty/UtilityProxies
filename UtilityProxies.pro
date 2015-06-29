QT       -= gui

TARGET = UtilityProxies
TEMPLATE = lib

DEFINES += UTILITYPROXIES_LIBRARY

SOURCES += \
    SubsetProxyModel.cpp \
    TranspositionProxyModel.cpp \

HEADERS +=\
    utilityproxies_global.h \
    SubsetProxyModel.h \
    TranspositionProxyModel.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}
