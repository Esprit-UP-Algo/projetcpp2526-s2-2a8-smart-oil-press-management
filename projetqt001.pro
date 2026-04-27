QT += core gui widgets sql printsupport charts network

QT += sql printsupport network charts

QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    arduino_zittech.cpp \
    chatbot.cpp \
    client.cpp \
    client_export.cpp \
    client_historique.cpp \
    client_prevision.cpp \
    client_recherche.cpp \
    client_stat.cpp \
    client_tri.cpp \
    connection.cpp \
    detectionprod.cpp \
    employe.cpp \
    employe_pdf.cpp \
    employe_search.cpp \
    employe_stats.cpp \
    employe_tri.cpp \
    estimation.cpp \
    exporterpartenaire.cpp \
    exportpdf.cpp \
    filterproduction.cpp \
    filtrepartenaire.cpp \
    gaugewidget.cpp \
    machine.cpp \
    machine_pdf.cpp \
    machine_search.cpp \
    machine_tri.cpp \
    jumeaunumerique.cpp \
    mailing.cpp \
    main.cpp \
    mainwindow.cpp \
    partenaire.cpp \
    Pdfproduction.cpp \
    predectionprod.cpp \
    production.cpp \
    recherche.cpp \
    rechproduction.cpp \
    statistique_partenaire.cpp \
    statistiques.cpp \
    Statproduction.cpp \
    stock.cpp \
    voicematieres.cpp

HEADERS += \
    arduino_zittech.h \
    chatbot.h \
    client.h \
    client_export.h \
    client_historique.h \
    client_prevision.h \
    client_recherche.h \
    client_stat.h \
    client_tri.h \
    connection.h \
    detectionprod.h \
    employe.h \
    employe_pdf.h \
    employe_search.h \
    employe_stats.h \
    employe_tri.h \
    estimation.h \
    exporterpartenaire.h \
    exportpdf.h \
    filterproduction.h \
    filtrepartenaire.h \
    gaugewidget.h \
    machine.h \
    machine_pdf.h \
    machine_search.h \
    machine_tri.h \
    jumeaunumerique.h \
    mailing.h \
    mainwindow.h \
    partenaire.h \
    Pdfproduction.h \
    predectionprod.h \
    production.h \
    recherche.h \
    rechproduction.h \
    statistique_partenaire.h \
    statistiques.h \
    Statproduction.h \
    stock.h \
    voicematieres.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc \
    rsssssssssss.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
