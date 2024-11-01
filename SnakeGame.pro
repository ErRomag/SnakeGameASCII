TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        GameEngine/GameEngine.cpp \
        GameEngine/ObjectGenerator.cpp \
        GameObject/Snake.cpp \
        Utilities/CollisionChecker.cpp \
        main.cpp

HEADERS += \
    GameEngine/GameEngine.h \
    GameEngine/ObjectGenerator.h \
    GameObject/BaseObject/AbsObject.h \
    GameObject/BaseObject/MovableObject.h \
    GameObject/Eat.h \
    GameObject/Snake.h \
    Utilities/CollisionChecker.h \
    Utilities/Direction.h \
    Utilities/Key.h \
    Utilities/Point.h
