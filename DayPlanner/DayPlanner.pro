TEMPLATE = app

QT += qml quick sql

CONFIG += qtquickcompiler

#DEFINES += CACHE_MONTH_DATA

win32: {
    INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include"
    LIBS += -L"C:/Program Files (x86)/Visual Leak Detector/lib/win64"
}

CONFIG += c++11

SOURCES += main.cpp \
    daymodel.cpp \
    daydata.cpp \
    dao/shiftdao.cpp \
    dao/db/database.cpp \
    dao/daobase.cpp \
    dao/db/dbdaobase.cpp \
    dao/mealdao.cpp \
    meallist.cpp \
    meal.cpp \
    dao/db/shiftdbdao.cpp \
    dao/db/dbdaofacade.cpp \
    dao/db/mealdbdao.cpp \
    dayplannerqmlglobals.cpp \
    dao/db/dbautoiddaobase.cpp \
    recipelist.cpp \
    dao/recipedao.cpp \
    dao/db/recipedbdao.cpp \
    qmlutils.cpp \
    shiftlist.cpp \
    dao/workoutdao.cpp \
    workout.cpp \
    dao/db/workoutdbdao.cpp \
    traininglist.cpp \
    dao/trainingdao.cpp \
    dao/db/trainingdbdao.cpp \
    workoutlist.cpp \
    recipe.cpp

RESOURCES += qml.qrc

DISTFILES += \
    main.qml \
    qml/DayItem.qml \
    qml/MealList.qml \
    qml/DoubleField.qml \
    qml/styles/ShiftComboStyle.qml \
    qml/styles/PlaceholderTextEditStyle.qml \
    qml/styles/DropdownStyle.qml \
    qml/PostfixTextField.qml \
    data/data.csv \
    qml/FilterTextInput.qml \
    qml/DaySummary.qml \
    qml/DayHeader.qml \
    qml/styles/BaseStyle.qml \
    qml/WorkoutList.qml \
    qml/TrainingSummary.qml \
    qml/MealSummary.qml \
    qml/styles/SmallButtonStyle.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include(../SortFilterProxyModel/SortFilterProxyModel.pri)

HEADERS += \
    daymodel.h \
    daydata.h \
    dao/shiftdao.h \
    dao/db/database.h \
    dao/dao.h \
    dao/daobase.h \
    dao/db/dbdaobase.h \
    dao/mealdao.h \
    meallist.h \
    meal.h \
    dao/db/shiftdbdao.h \
    dao/db/dbdaofacade.h \
    dao/db/mealdbdao.h \
    dayplannerqmlglobals.h \
    dao/db/dbautoiddaobase.h \
    recipelist.h \
    dao/recipedao.h \
    dao/db/recipedbdao.h \
    qmlutils.h \
    shiftlist.h \
    dao/workoutdao.h \
    workout.h \
    dao/db/workoutdbdao.h \
    traininglist.h \
    dao/trainingdao.h \
    dao/db/trainingdbdao.h \
    workoutlist.h \
    recipe.h
