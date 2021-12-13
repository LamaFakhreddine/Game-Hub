QT += widgets
QT += core
QT += charts
QT += multimedia

SOURCES += \
    butb.cpp \
    butblack.cpp \
    butg.cpp \
    butp.cpp \
    centering.cpp \
    g1_info.cpp \
    g1_settings.cpp \
    g1_setup.cpp \
    g1_startmenu.cpp \
    g2_settings.cpp \
    g2_setup.cpp \
    g2_startmenu.cpp \
    gamelost.cpp \
    gamewon.cpp \
    jsonhandler.cpp \
    main.cpp \
    noturns.cpp \
    playasguest.cpp \
    quests.cpp \
    scene1.cpp \
    signinpage.cpp \
    signuppage.cpp \
    account.cpp \
    account_dashboard.cpp \
    account_sidebar.cpp \
    timeup.cpp

HEADERS += \
    butb.h \
    butblack.h \
    butg.h \
    butp.h \
    centering.h \
    g1_info.h \
    g1_settings.h \
    g1_setup.h \
    g1_startmenu.h \
    g2_settings.h \
    g2_setup.h \
    g2_startmenu.h \
    gamelost.h \
    gamewon.h \
    jsonhandler.h \
    noturns.h \
    playasguest.h \
    quests.h \
    scene1.h \
    signinpage.h \
    signuppage.h \
    account.h \
    account_dashboard.h \
    account_sidebar.h \
    timeup.h

DISTFILES += \
    ../../trial.json \
    assets/battleships.png \
    assets/bs-settings.png \
    assets/bs-time-up.png \
    data.json

RESOURCES += \
    assets/resources.qrc

OBJECTS_DIR += ../project_/bin
