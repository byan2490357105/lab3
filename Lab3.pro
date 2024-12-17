QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctoreditview.cpp \
    doctorview.cpp \
    historyeditview.cpp \
    historyview.cpp \
    idatabase.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    medicaleditview.cpp \
    medicalview.cpp \
    patienteditview.cpp \
    patientview.cpp \
    welcomeview.cpp

HEADERS += \
    doctoreditview.h \
    doctorview.h \
    historyeditview.h \
    historyview.h \
    idatabase.h \
    loginview.h \
    masterview.h \
    medicaleditview.h \
    medicalview.h \
    patienteditview.h \
    patientview.h \
    welcomeview.h

FORMS += \
    doctoreditview.ui \
    doctorview.ui \
    historyeditview.ui \
    historyview.ui \
    loginview.ui \
    masterview.ui \
    medicaleditview.ui \
    medicalview.ui \
    patienteditview.ui \
    patientview.ui \
    welcomeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
