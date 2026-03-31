QT += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Atelier_Connexion
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG  += c++11

# ── Sources ──────────────────────────────────────────────────
SOURCES += \
    main.cpp           \
    connection.cpp     \
    employe.cpp        \
    employe_search.cpp \
    employe_stats.cpp  \
    employe_pdf.cpp    \
    machine.cpp        \
    machine_search.cpp \
    machine_pdf.cpp    \
    mainwindow.cpp

# ── Headers ──────────────────────────────────────────────────
HEADERS += \
    connection.h     \
    employe.h        \
    employe_search.h \
    employe_stats.h  \
    employe_pdf.h    \
    machine.h        \
    machine_search.h \
    machine_pdf.h    \
    mainwindow.h

# ── Formulaires Qt Designer ───────────────────────────────────
FORMS += mainwindow.ui

# ── Déploiement ───────────────────────────────────────────────
qnx:  target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
