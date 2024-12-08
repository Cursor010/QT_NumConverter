/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLineEdit *lineInputSystem;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLineEdit *lineResNum;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLineEdit *lineResSystem;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLineEdit *lineInputNum;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(449, 218);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        lineInputSystem = new QLineEdit(centralwidget);
        lineInputSystem->setObjectName("lineInputSystem");

        verticalLayout_3->addWidget(lineInputSystem);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        lineResNum = new QLineEdit(centralwidget);
        lineResNum->setObjectName("lineResNum");

        verticalLayout_2->addWidget(lineResNum);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        lineResSystem = new QLineEdit(centralwidget);
        lineResSystem->setObjectName("lineResSystem");

        verticalLayout->addWidget(lineResSystem);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout_4->addWidget(label);

        lineInputNum = new QLineEdit(centralwidget);
        lineInputNum->setObjectName("lineInputNum");

        verticalLayout_4->addWidget(lineInputNum);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 2);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        gridLayout->addWidget(pushButton_3, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 449, 17));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Enter current system:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "calculate", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Result", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Enter result system:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Enter number:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "read file", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "write to file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
