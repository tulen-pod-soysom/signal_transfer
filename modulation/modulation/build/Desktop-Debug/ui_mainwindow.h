/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCustomPlot *widget;
    QCustomPlot *widget_2;
    QCustomPlot *widget_3;
    QCustomPlot *widget_4;
    QCustomPlot *widget_5;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *LineEdit;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *Label_2;
    QLineEdit *LineEdit_2;
    QLabel *Label_3;
    QLineEdit *LineEdit_3;
    QCustomPlot *widget_6;
    QCustomPlot *widget_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1302, 698);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(370, 10, 921, 151));
        widget_2 = new QCustomPlot(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(370, 170, 921, 91));
        widget_3 = new QCustomPlot(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(370, 270, 921, 91));
        widget_4 = new QCustomPlot(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(10, 250, 351, 81));
        widget_5 = new QCustomPlot(centralwidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(370, 430, 921, 101));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 351, 171));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        Label = new QLabel(formLayoutWidget);
        Label->setObjectName(QString::fromUtf8("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        LineEdit = new QLineEdit(formLayoutWidget);
        LineEdit->setObjectName(QString::fromUtf8("LineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEdit);

        radioButton = new QRadioButton(formLayoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        formLayout->setWidget(2, QFormLayout::LabelRole, radioButton);

        radioButton_2 = new QRadioButton(formLayoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, radioButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer_2);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Label_2);

        LineEdit_2 = new QLineEdit(formLayoutWidget);
        LineEdit_2->setObjectName(QString::fromUtf8("LineEdit_2"));
        LineEdit_2->setReadOnly(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, LineEdit_2);

        Label_3 = new QLabel(formLayoutWidget);
        Label_3->setObjectName(QString::fromUtf8("Label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_3);

        LineEdit_3 = new QLineEdit(formLayoutWidget);
        LineEdit_3->setObjectName(QString::fromUtf8("LineEdit_3"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LineEdit_3);

        widget_6 = new QCustomPlot(centralwidget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(370, 540, 921, 101));
        widget_7 = new QCustomPlot(centralwidget);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(10, 340, 351, 301));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1302, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\264\320\260\320\262\320\260\320\265\320\274\320\276\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        LineEdit->setText(QCoreApplication::translate("MainWindow", "11010010110100100011", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "\320\244\320\2342", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "\320\244\320\2344", nullptr));
        Label_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \321\204\320\260\320\267\320\260 \321\201\320\270\320\263\320\275\320\260\320\273\320\260", nullptr));
        Label_3->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\267\320\260 \320\277\321\200\320\270\320\265\320\274\320\275\320\270\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
