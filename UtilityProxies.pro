QT       -= gui

TARGET = UtilityProxies
TEMPLATE = lib

DEFINES += UTILITYPROXIES_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}
