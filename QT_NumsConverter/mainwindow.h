#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "converter.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QHash>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString readFile(const QString &filePath);

};
#endif // MAINWINDOW_H
