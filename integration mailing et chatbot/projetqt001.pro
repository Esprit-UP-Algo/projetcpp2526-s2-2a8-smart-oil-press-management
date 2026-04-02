QT += core gui widgets sql printsupport charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    chatbot.cpp \
    client.cpp \
    client_achat.cpp \
    client_export.cpp \
    client_historique.cpp \
    client_prevision.cpp \
    client_recherche.cpp \
    client_stat.cpp \
    client_tri.cpp \
    connection.cpp \
    employe.cpp \
    employe_pdf.cpp \
    employe_search.cpp \
    employe_stats.cpp \
    estimation.cpp \
    exporterpartenaire.cpp \
    exportpdf.cpp \
    filtrepartenaire.cpp \
    machine.cpp \
    machine_pdf.cpp \
    machine_search.cpp \
    mailing.cpp \
    main.cpp \
    mainwindow.cpp \
    partenaire.cpp \
    Pdfproduction.cpp \
    production.cpp \
    recherche.cpp \
    statistique_partenaire.cpp \
    statistiques.cpp \
    Statproduction.cpp \
    stock.cpp

HEADERS += \
    chatbot.h \
    client.h \
    client_achat.h \
    client_export.h \
    client_historique.h \
    client_prevision.h \
    client_recherche.h \
    client_stat.h \
    client_tri.h \
    connection.h \
    employe.h \
    employe_pdf.h \
    employe_search.h \
    employe_stats.h \
    estimation.h \
    exporterpartenaire.h \
    exportpdf.h \
    filtrepartenaire.h \
    machine.h \
    machine_pdf.h \
    machine_search.h \
    mailing.h \
    mainwindow.h \
    partenaire.h \
    Pdfproduction.h \
    production.h \
    recherche.h \
    statistique_partenaire.h \
    statistiques.h \
    Statproduction.h \
    stock.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    rsssssssssss.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
