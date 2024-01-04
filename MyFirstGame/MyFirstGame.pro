QT += core gui multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bullet.cpp \
    Character.cpp \
    Enemy.cpp \
    EnemyChild.cpp \
    Game.cpp \
    Health.cpp \
    Player.cpp \
    Score.cpp \
    Timer.cpp \
    main.cpp \
    scene.cpp

HEADERS += \
    Bullet.h \
    Character.h \
    Enemy.h \
    EnemyChild.h \
    Game.h \
    Health.h \
    Player.h \
    Score.h \
    Timer.h \
    scene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/background.png \
    images/red.png \
    images/yellow.png

RESOURCES += \
    qre.qrc

