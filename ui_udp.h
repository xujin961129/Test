/********************************************************************************
** Form generated from reading UI file 'udp.ui'
**
** Created: Thu Jan 12 17:13:04 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDP_H
#define UI_UDP_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UDP
{
public:
    QLabel *label_17;
    QLineEdit *UDPSenderPortlineEdit;
    QLabel *label_27;
    QLabel *label_26;
    QLineEdit *UDPFarPortlineEdit;
    QLabel *label_18;
    QComboBox *UDPServerIPcomboBox;
    QLineEdit *UDPFarIPlineEdit;
    QPushButton *OKpushButton;
    QLabel *UDPServerStatelabel;

    void setupUi(QDialog *UDP)
    {
        if (UDP->objectName().isEmpty())
            UDP->setObjectName(QString::fromUtf8("UDP"));
        UDP->resize(369, 109);
        label_17 = new QLabel(UDP);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(12, 25, 48, 12));
        UDPSenderPortlineEdit = new QLineEdit(UDP);
        UDPSenderPortlineEdit->setObjectName(QString::fromUtf8("UDPSenderPortlineEdit"));
        UDPSenderPortlineEdit->setGeometry(QRect(221, 20, 41, 20));
        label_27 = new QLabel(UDP);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(190, 50, 31, 20));
        label_26 = new QLabel(UDP);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(190, 20, 31, 20));
        UDPFarPortlineEdit = new QLineEdit(UDP);
        UDPFarPortlineEdit->setObjectName(QString::fromUtf8("UDPFarPortlineEdit"));
        UDPFarPortlineEdit->setGeometry(QRect(221, 50, 41, 20));
        label_18 = new QLabel(UDP);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(12, 55, 48, 12));
        UDPServerIPcomboBox = new QComboBox(UDP);
        UDPServerIPcomboBox->setObjectName(QString::fromUtf8("UDPServerIPcomboBox"));
        UDPServerIPcomboBox->setGeometry(QRect(60, 20, 111, 20));
        UDPServerIPcomboBox->setEditable(false);
        UDPFarIPlineEdit = new QLineEdit(UDP);
        UDPFarIPlineEdit->setObjectName(QString::fromUtf8("UDPFarIPlineEdit"));
        UDPFarIPlineEdit->setGeometry(QRect(60, 50, 111, 20));
        OKpushButton = new QPushButton(UDP);
        OKpushButton->setObjectName(QString::fromUtf8("OKpushButton"));
        OKpushButton->setGeometry(QRect(280, 50, 75, 23));
        UDPServerStatelabel = new QLabel(UDP);
        UDPServerStatelabel->setObjectName(QString::fromUtf8("UDPServerStatelabel"));
        UDPServerStatelabel->setGeometry(QRect(12, 80, 191, 20));

        retranslateUi(UDP);

        QMetaObject::connectSlotsByName(UDP);
    } // setupUi

    void retranslateUi(QDialog *UDP)
    {
        UDP->setWindowTitle(QApplication::translate("UDP", "UDP\345\217\202\346\225\260\351\205\215\347\275\256", 0));
        label_17->setText(QApplication::translate("UDP", "\346\234\254\346\234\272IP\357\274\232", 0));
        UDPSenderPortlineEdit->setText(QApplication::translate("UDP", "2501", 0));
        label_27->setText(QApplication::translate("UDP", "\347\253\257\345\217\243\357\274\232", 0));
        label_26->setText(QApplication::translate("UDP", "\347\253\257\345\217\243\357\274\232", 0));
        UDPFarPortlineEdit->setText(QApplication::translate("UDP", "2500", 0));
        label_18->setText(QApplication::translate("UDP", "\347\233\256\346\240\207IP\357\274\232", 0));
        UDPFarIPlineEdit->setText(QApplication::translate("UDP", "169.254.25.129", 0));
        OKpushButton->setText(QApplication::translate("UDP", "\347\241\256 \345\256\232", 0));
        UDPServerStatelabel->setText(QApplication::translate("UDP", "Ready", 0));
    } // retranslateUi

};

namespace Ui {
    class UDP: public Ui_UDP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDP_H
