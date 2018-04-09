/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEdge_List;
    QAction *actionAdjacency_List;
    QAction *actionIncidence_Matrix;
    QAction *actionAdjacency_Matrix;
    QWidget *centralWidget;
    QPushButton *pbVizualize;
    QGroupBox *gbMetrics;
    QLineEdit *leConnectedComponent;
    QLabel *lblNodesCnt;
    QLineEdit *leNodesCnt;
    QLineEdit *leEdgesCnt;
    QLabel *lblEdgesCnt;
    QLabel *lblGraphPower;
    QLabel *lblRadius;
    QLineEdit *leCircuitRank;
    QLabel *lblCircuitRank;
    QLineEdit *leRadius;
    QLineEdit *leDiameter;
    QLabel *lblDiameter;
    QLabel *lblConnectedComponent;
    QLineEdit *leGraphPower;
    QPushButton *pbCalcMetrics;
    QLineEdit *leIsTree;
    QLabel *lblIsTree;
    QMenuBar *menuBar;
    QMenu *menuOpen;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(292, 372);
        actionEdge_List = new QAction(MainWindow);
        actionEdge_List->setObjectName(QStringLiteral("actionEdge_List"));
        actionAdjacency_List = new QAction(MainWindow);
        actionAdjacency_List->setObjectName(QStringLiteral("actionAdjacency_List"));
        actionIncidence_Matrix = new QAction(MainWindow);
        actionIncidence_Matrix->setObjectName(QStringLiteral("actionIncidence_Matrix"));
        actionAdjacency_Matrix = new QAction(MainWindow);
        actionAdjacency_Matrix->setObjectName(QStringLiteral("actionAdjacency_Matrix"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pbVizualize = new QPushButton(centralWidget);
        pbVizualize->setObjectName(QStringLiteral("pbVizualize"));
        pbVizualize->setGeometry(QRect(20, 320, 251, 21));
        gbMetrics = new QGroupBox(centralWidget);
        gbMetrics->setObjectName(QStringLiteral("gbMetrics"));
        gbMetrics->setGeometry(QRect(10, 10, 271, 301));
        leConnectedComponent = new QLineEdit(gbMetrics);
        leConnectedComponent->setObjectName(QStringLiteral("leConnectedComponent"));
        leConnectedComponent->setGeometry(QRect(150, 210, 113, 21));
        leConnectedComponent->setReadOnly(true);
        lblNodesCnt = new QLabel(gbMetrics);
        lblNodesCnt->setObjectName(QStringLiteral("lblNodesCnt"));
        lblNodesCnt->setGeometry(QRect(10, 30, 121, 16));
        leNodesCnt = new QLineEdit(gbMetrics);
        leNodesCnt->setObjectName(QStringLiteral("leNodesCnt"));
        leNodesCnt->setGeometry(QRect(150, 30, 113, 21));
        leNodesCnt->setReadOnly(true);
        leEdgesCnt = new QLineEdit(gbMetrics);
        leEdgesCnt->setObjectName(QStringLiteral("leEdgesCnt"));
        leEdgesCnt->setGeometry(QRect(150, 60, 113, 21));
        leEdgesCnt->setReadOnly(true);
        lblEdgesCnt = new QLabel(gbMetrics);
        lblEdgesCnt->setObjectName(QStringLiteral("lblEdgesCnt"));
        lblEdgesCnt->setGeometry(QRect(10, 60, 121, 16));
        lblGraphPower = new QLabel(gbMetrics);
        lblGraphPower->setObjectName(QStringLiteral("lblGraphPower"));
        lblGraphPower->setGeometry(QRect(10, 120, 121, 16));
        lblRadius = new QLabel(gbMetrics);
        lblRadius->setObjectName(QStringLiteral("lblRadius"));
        lblRadius->setGeometry(QRect(10, 150, 121, 16));
        leCircuitRank = new QLineEdit(gbMetrics);
        leCircuitRank->setObjectName(QStringLiteral("leCircuitRank"));
        leCircuitRank->setGeometry(QRect(150, 180, 113, 21));
        leCircuitRank->setReadOnly(true);
        lblCircuitRank = new QLabel(gbMetrics);
        lblCircuitRank->setObjectName(QStringLiteral("lblCircuitRank"));
        lblCircuitRank->setGeometry(QRect(10, 180, 121, 16));
        leRadius = new QLineEdit(gbMetrics);
        leRadius->setObjectName(QStringLiteral("leRadius"));
        leRadius->setGeometry(QRect(150, 150, 113, 21));
        leRadius->setReadOnly(true);
        leDiameter = new QLineEdit(gbMetrics);
        leDiameter->setObjectName(QStringLiteral("leDiameter"));
        leDiameter->setGeometry(QRect(150, 90, 113, 21));
        leDiameter->setReadOnly(true);
        lblDiameter = new QLabel(gbMetrics);
        lblDiameter->setObjectName(QStringLiteral("lblDiameter"));
        lblDiameter->setGeometry(QRect(10, 90, 121, 16));
        lblConnectedComponent = new QLabel(gbMetrics);
        lblConnectedComponent->setObjectName(QStringLiteral("lblConnectedComponent"));
        lblConnectedComponent->setGeometry(QRect(10, 210, 121, 16));
        leGraphPower = new QLineEdit(gbMetrics);
        leGraphPower->setObjectName(QStringLiteral("leGraphPower"));
        leGraphPower->setGeometry(QRect(150, 120, 113, 21));
        leGraphPower->setReadOnly(true);
        pbCalcMetrics = new QPushButton(gbMetrics);
        pbCalcMetrics->setObjectName(QStringLiteral("pbCalcMetrics"));
        pbCalcMetrics->setGeometry(QRect(10, 270, 80, 21));
        leIsTree = new QLineEdit(gbMetrics);
        leIsTree->setObjectName(QStringLiteral("leIsTree"));
        leIsTree->setGeometry(QRect(150, 240, 113, 21));
        leIsTree->setReadOnly(true);
        lblIsTree = new QLabel(gbMetrics);
        lblIsTree->setObjectName(QStringLiteral("lblIsTree"));
        lblIsTree->setGeometry(QRect(10, 240, 121, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 292, 20));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuOpen->menuAction());
        menuOpen->addAction(actionEdge_List);
        menuOpen->addAction(actionAdjacency_List);
        menuOpen->addAction(actionIncidence_Matrix);
        menuOpen->addAction(actionAdjacency_Matrix);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionEdge_List->setText(QApplication::translate("MainWindow", "Edge List", nullptr));
        actionAdjacency_List->setText(QApplication::translate("MainWindow", "Adjacency List", nullptr));
        actionIncidence_Matrix->setText(QApplication::translate("MainWindow", "Incidence Matrix", nullptr));
        actionAdjacency_Matrix->setText(QApplication::translate("MainWindow", "Adjacency Matrix", nullptr));
        pbVizualize->setText(QApplication::translate("MainWindow", "Vizualize", nullptr));
        gbMetrics->setTitle(QApplication::translate("MainWindow", "Metrics", nullptr));
        lblNodesCnt->setText(QApplication::translate("MainWindow", "Nodes count:", nullptr));
        lblEdgesCnt->setText(QApplication::translate("MainWindow", "Edges count:", nullptr));
        lblGraphPower->setText(QApplication::translate("MainWindow", "Graph Power:", nullptr));
        lblRadius->setText(QApplication::translate("MainWindow", "Radius:", nullptr));
        lblCircuitRank->setText(QApplication::translate("MainWindow", "Circuit Rank:", nullptr));
        lblDiameter->setText(QApplication::translate("MainWindow", "Diameter:", nullptr));
        lblConnectedComponent->setText(QApplication::translate("MainWindow", "Connected Component:", nullptr));
        pbCalcMetrics->setText(QApplication::translate("MainWindow", "Evaluate", nullptr));
        lblIsTree->setText(QApplication::translate("MainWindow", "Is tree:", nullptr));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Load from...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
