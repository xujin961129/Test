/********************************************************************************
** Form generated from reading UI file 'com.ui'
**
** Created: Thu Jan 12 17:13:04 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COM_H
#define UI_COM_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_COM
{
public:
    QPushButton *OKpushButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_23;
    QComboBox *portNameComboBox;
    QLabel *label_20;
    QComboBox *baudRateComboBox;
    QLabel *label_19;
    QComboBox *dataBitsComboBox;
    QLabel *label_25;
    QComboBox *parityComboBox;
    QLabel *label_22;
    QComboBox *stopBitsComboBox;

    void setupUi(QDialog *COM)
    {
        if (COM->objectName().isEmpty())
            COM->setObjectName(QString::fromUtf8("COM"));
        COM->resize(292, 191);
        OKpushButton = new QPushButton(COM);
        OKpushButton->setObjectName(QString::fromUtf8("OKpushButton"));
        OKpushButton->setGeometry(QRect(200, 143, 75, 23));
        layoutWidget = new QWidget(COM);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 15, 151, 161));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 0, 0, 1, 1);

        portNameComboBox = new QComboBox(layoutWidget);
        portNameComboBox->setObjectName(QString::fromUtf8("portNameComboBox"));

        gridLayout->addWidget(portNameComboBox, 0, 1, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 1, 0, 1, 1);

        baudRateComboBox = new QComboBox(layoutWidget);
        baudRateComboBox->setObjectName(QString::fromUtf8("baudRateComboBox"));

        gridLayout->addWidget(baudRateComboBox, 1, 1, 1, 1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 2, 0, 1, 1);

        dataBitsComboBox = new QComboBox(layoutWidget);
        dataBitsComboBox->setObjectName(QString::fromUtf8("dataBitsComboBox"));

        gridLayout->addWidget(dataBitsComboBox, 2, 1, 1, 1);

        label_25 = new QLabel(layoutWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 3, 0, 1, 1);

        parityComboBox = new QComboBox(layoutWidget);
        parityComboBox->setObjectName(QString::fromUtf8("parityComboBox"));

        gridLayout->addWidget(parityComboBox, 3, 1, 1, 1);

        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout->addWidget(label_22, 4, 0, 1, 1);

        stopBitsComboBox = new QComboBox(layoutWidget);
        stopBitsComboBox->setObjectName(QString::fromUtf8("stopBitsComboBox"));

        gridLayout->addWidget(stopBitsComboBox, 4, 1, 1, 1);


        retranslateUi(COM);

        QMetaObject::connectSlotsByName(COM);
    } // setupUi

    void retranslateUi(QDialog *COM)
    {
        COM->setWindowTitle(QApplication::translate("COM", "Dialog", 0));
        OKpushButton->setText(QApplication::translate("COM", "\347\241\256 \345\256\232", 0));
        label_23->setText(QApplication::translate("COM", "\344\270\262\345\217\243\357\274\232", 0));
        portNameComboBox->clear();
        portNameComboBox->insertItems(0, QStringList()
         << QApplication::translate("COM", "COM1", 0)
         << QApplication::translate("COM", "COM2", 0)
         << QApplication::translate("COM", "COM3", 0)
         << QApplication::translate("COM", "COM4", 0)
         << QApplication::translate("COM", "COM5", 0)
         << QApplication::translate("COM", "COM6", 0)
        );
        label_20->setText(QApplication::translate("COM", "\346\263\242\347\211\271\347\216\207\357\274\232", 0));
        baudRateComboBox->clear();
        baudRateComboBox->insertItems(0, QStringList()
         << QApplication::translate("COM", "9600", 0)
         << QApplication::translate("COM", "115200", 0)
        );
        label_19->setText(QApplication::translate("COM", "\346\225\260\346\215\256\344\275\215\357\274\232", 0));
        dataBitsComboBox->clear();
        dataBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("COM", "8", 0)
         << QApplication::translate("COM", "7", 0)
        );
        label_25->setText(QApplication::translate("COM", "\346\240\241\351\252\214\344\275\215\357\274\232", 0));
        parityComboBox->clear();
        parityComboBox->insertItems(0, QStringList()
         << QApplication::translate("COM", "\346\227\240", 0)
         << QApplication::translate("COM", "\345\245\207", 0)
         << QApplication::translate("COM", "\345\201\266", 0)
        );
        label_22->setText(QApplication::translate("COM", "\345\201\234\346\255\242\344\275\215\357\274\232", 0));
        stopBitsComboBox->clear();
        stopBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("COM", "1", 0)
         << QApplication::translate("COM", "2", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class COM: public Ui_COM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COM_H
