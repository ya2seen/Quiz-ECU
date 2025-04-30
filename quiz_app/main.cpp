#include "MainWindow.h"
#include "DataManager.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application style
    QFile styleFile(":/styles/style.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&styleFile);
        app.setStyleSheet(stream.readAll());
        styleFile.close();
    }
    
    // Create sample data
    DataManager::getInstance().createSampleData();
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
} 