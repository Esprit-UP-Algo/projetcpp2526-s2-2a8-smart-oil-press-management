#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Test database connection
    Connection c;
    bool test = c.createconnect();

    if(test)
    {
        // Show main window if connection successful
        MainWindow w;
        w.show();

        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful!\n"
                                             "Database is ready to use."),
                                 QMessageBox::Ok);

        return a.exec();
    }
    else
    {
        // Show error message if connection failed
        QMessageBox::critical(nullptr, QObject::tr("Database Connection Error"),
                              QObject::tr("Failed to connect to database.\n"
                                          "Please check your Oracle configuration.\n\n"
                                          "Click OK to exit."),
                              QMessageBox::Ok);
        return -1;
    }
}
