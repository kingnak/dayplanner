TEMPLATE = app

QT += qml quick sql

#DEFINES += CACHE_MONTH_DATA

CONFIG += c++11

SOURCES += main.cpp \
    daymodel.cpp \
    daydata.cpp \
    db/shiftdao.cpp \
    db/database.cpp \
    db/daobase.cpp \
    db/dbdaobase.cpp \
    db/mealdao.cpp \
    meallist.cpp \
    meal.cpp

RESOURCES += qml.qrc

DISTFILES += \
    main.qml \
    qml/DayItem.qml \
    qml/MealList.qml \
    qml/styles/ShiftComboStyle.qml \
    qml/styles/PlaceholderTextEditStyle.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    daymodel.h \
    daydata.h \
    db/shiftdao.h \
    db/database.h \
    db/dao.h \
    db/daobase.h \
    db/dbdaobase.h \
    db/mealdao.h \
    meallist.h \
    meal.h
