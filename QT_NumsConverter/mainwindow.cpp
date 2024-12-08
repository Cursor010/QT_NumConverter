#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString number = ui->lineInputNum->text();
    QString fromBase = ui->lineInputSystem->text();
    QString toBase = ui->lineResSystem->text();

    Converter conv;
    QString res = conv.convert(number, fromBase, toBase);
    ui->lineResNum->setText(res);
}

void MainWindow::on_pushButton_2_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");

    if (!filePath.isEmpty()) {
        QString content = readFile(filePath);
        ui->lineInputNum->setText(content);
    }
}

QString MainWindow::readFile(const QString &filePath) {
    QFile file(filePath);
    QString content;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл:" << file.errorString();
        return content;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        content.append(in.readLine() + "\n");
    }

    file.close();
    return content;
}

void MainWindow::on_pushButton_3_clicked() {
    QString lineresnum = ui->lineResNum->text();

    QFile file("res.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << lineresnum;

    file.close();
}
