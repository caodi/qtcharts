
TARGET = qtchartsqml2
CXX_MODULE = charts

QT += qml quick
QT += charts charts-private

# Only build qml plugin static if Qt itself is also built static
!contains(QT_CONFIG, static): CONFIG -= static staticlib

include($$PWD/designer/designer.pri)

SOURCES += \
    chartsqml2_plugin.cpp \
    declarativechart.cpp \
    declarativexypoint.cpp \
    declarativexyseries.cpp \
    declarativelineseries.cpp \
    declarativesplineseries.cpp \
    declarativeareaseries.cpp \
    declarativescatterseries.cpp \
    declarativepieseries.cpp \
    declarativebarseries.cpp \
    declarativecategoryaxis.cpp \
    declarativemargins.cpp \
    declarativeaxes.cpp \
    declarativepolarchart.cpp \
    declarativeboxplotseries.cpp \
    declarativechartnode.cpp \
    declarativerendernode.cpp

HEADERS += \
    declarativechart.h \
    declarativexypoint.h \
    declarativexyseries.h \
    declarativelineseries.h \
    declarativesplineseries.h \
    declarativeareaseries.h \
    declarativescatterseries.h \
    declarativepieseries.h \
    declarativebarseries.h \
    declarativecategoryaxis.h \
    declarativemargins.h \
    declarativeaxes.h \
    declarativepolarchart.h \
    declarativeboxplotseries.h \
    declarativechartnode.h \
    declarativerendernode.h

OTHER_FILES = qmldir

load(qml_plugin)

win32 {
    CONFIG += skip_target_version_ext
    VERSION = $$MODULE_VERSION
    QMAKE_TARGET_PRODUCT = "Qt Charts (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Charts QML plugin for Qt."
}

QML_FILES += \
    $$PWD/plugins.qmltypes
