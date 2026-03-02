#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ✅ Utilisation correcte du Singleton
    bool test = Connection::instance()->createConnect();

    if(test)
    {
        MainWindow w;
        w.show();

        QMessageBox::information(nullptr,
                                 QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful!\nDatabase ready."),
                                 QMessageBox::Ok);

        return a.exec();
    }
    else
    {
        QMessageBox::critical(nullptr,
                              QObject::tr("Database Connection Error"),
                              QObject::tr("Failed to connect to database."),
                              QMessageBox::Ok);
        return -1;
    }
}
