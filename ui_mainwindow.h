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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
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
    QLabel *lblIsOrientiered;
    QRadioButton *rbOrient;
    QRadioButton *rbNotOrient;
    QGroupBox *gbNodeOperations;
    QPushButton *pbAddNode;
    QPushButton *pbDeleteNode;
    QLabel *lblNodeName;
    QLineEdit *leNode;
    QGroupBox *gbEdgeOpertions;
    QPushButton *pbAddEdge;
    QPushButton *pbDeleteEdge;
    QLabel *lblNodeFromName;
    QLineEdit *leNodeFromName;
    QLabel *lblNodeToName;
    QLineEdit *leNodeToName;
    QLabel *lblEdgeWeight;
    QLineEdit *leEdgeWeight;
    QGroupBox *bgOther;
    QPlainTextEdit *pteOther;
    QPushButton *pbDFS;
    QLineEdit *leDFSNodeFrom;
    QMenuBar *menuBar;
    QMenu *menuOpen;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(707, 392);
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
        pbVizualize->setGeometry(QRect(20, 340, 81, 21));
        gbMetrics = new QGroupBox(centralWidget);
        gbMetrics->setObjectName(QStringLiteral("gbMetrics"));
        gbMetrics->setGeometry(QRect(10, 10, 481, 191));
        leConnectedComponent = new QLineEdit(gbMetrics);
        leConnectedComponent->setObjectName(QStringLiteral("leConnectedComponent"));
        leConnectedComponent->setGeometry(QRect(350, 90, 113, 21));
        leConnectedComponent->setReadOnly(true);
        lblNodesCnt = new QLabel(gbMetrics);
        lblNodesCnt->setObjectName(QStringLiteral("lblNodesCnt"));
        lblNodesCnt->setGeometry(QRect(10, 30, 121, 16));
        leNodesCnt = new QLineEdit(gbMetrics);
        leNodesCnt->setObjectName(QStringLiteral("leNodesCnt"));
        leNodesCnt->setGeometry(QRect(90, 30, 113, 21));
        leNodesCnt->setReadOnly(true);
        leEdgesCnt = new QLineEdit(gbMetrics);
        leEdgesCnt->setObjectName(QStringLiteral("leEdgesCnt"));
        leEdgesCnt->setGeometry(QRect(90, 60, 113, 21));
        leEdgesCnt->setReadOnly(true);
        lblEdgesCnt = new QLabel(gbMetrics);
        lblEdgesCnt->setObjectName(QStringLiteral("lblEdgesCnt"));
        lblEdgesCnt->setGeometry(QRect(10, 60, 121, 16));
        lblGraphPower = new QLabel(gbMetrics);
        lblGraphPower->setObjectName(QStringLiteral("lblGraphPower"));
        lblGraphPower->setGeometry(QRect(10, 120, 121, 16));
        lblRadius = new QLabel(gbMetrics);
        lblRadius->setObjectName(QStringLiteral("lblRadius"));
        lblRadius->setGeometry(QRect(230, 30, 121, 16));
        leCircuitRank = new QLineEdit(gbMetrics);
        leCircuitRank->setObjectName(QStringLiteral("leCircuitRank"));
        leCircuitRank->setGeometry(QRect(350, 60, 113, 21));
        leCircuitRank->setReadOnly(true);
        lblCircuitRank = new QLabel(gbMetrics);
        lblCircuitRank->setObjectName(QStringLiteral("lblCircuitRank"));
        lblCircuitRank->setGeometry(QRect(230, 60, 121, 16));
        leRadius = new QLineEdit(gbMetrics);
        leRadius->setObjectName(QStringLiteral("leRadius"));
        leRadius->setGeometry(QRect(350, 30, 113, 21));
        leRadius->setReadOnly(true);
        leDiameter = new QLineEdit(gbMetrics);
        leDiameter->setObjectName(QStringLiteral("leDiameter"));
        leDiameter->setGeometry(QRect(90, 90, 113, 21));
        leDiameter->setReadOnly(true);
        lblDiameter = new QLabel(gbMetrics);
        lblDiameter->setObjectName(QStringLiteral("lblDiameter"));
        lblDiameter->setGeometry(QRect(10, 90, 121, 16));
        lblConnectedComponent = new QLabel(gbMetrics);
        lblConnectedComponent->setObjectName(QStringLiteral("lblConnectedComponent"));
        lblConnectedComponent->setGeometry(QRect(230, 90, 121, 16));
        leGraphPower = new QLineEdit(gbMetrics);
        leGraphPower->setObjectName(QStringLiteral("leGraphPower"));
        leGraphPower->setGeometry(QRect(90, 120, 113, 21));
        leGraphPower->setReadOnly(true);
        pbCalcMetrics = new QPushButton(gbMetrics);
        pbCalcMetrics->setObjectName(QStringLiteral("pbCalcMetrics"));
        pbCalcMetrics->setGeometry(QRect(10, 160, 80, 21));
        leIsTree = new QLineEdit(gbMetrics);
        leIsTree->setObjectName(QStringLiteral("leIsTree"));
        leIsTree->setGeometry(QRect(350, 120, 113, 21));
        leIsTree->setReadOnly(true);
        lblIsTree = new QLabel(gbMetrics);
        lblIsTree->setObjectName(QStringLiteral("lblIsTree"));
        lblIsTree->setGeometry(QRect(230, 120, 121, 16));
        lblIsOrientiered = new QLabel(centralWidget);
        lblIsOrientiered->setObjectName(QStringLiteral("lblIsOrientiered"));
        lblIsOrientiered->setGeometry(QRect(20, 310, 71, 16));
        rbOrient = new QRadioButton(centralWidget);
        rbOrient->setObjectName(QStringLiteral("rbOrient"));
        rbOrient->setGeometry(QRect(100, 310, 41, 19));
        rbOrient->setChecked(true);
        rbNotOrient = new QRadioButton(centralWidget);
        rbNotOrient->setObjectName(QStringLiteral("rbNotOrient"));
        rbNotOrient->setEnabled(true);
        rbNotOrient->setGeometry(QRect(150, 310, 41, 19));
        gbNodeOperations = new QGroupBox(centralWidget);
        gbNodeOperations->setObjectName(QStringLiteral("gbNodeOperations"));
        gbNodeOperations->setGeometry(QRect(10, 210, 191, 91));
        pbAddNode = new QPushButton(gbNodeOperations);
        pbAddNode->setObjectName(QStringLiteral("pbAddNode"));
        pbAddNode->setGeometry(QRect(10, 60, 80, 21));
        pbDeleteNode = new QPushButton(gbNodeOperations);
        pbDeleteNode->setObjectName(QStringLiteral("pbDeleteNode"));
        pbDeleteNode->setGeometry(QRect(100, 60, 80, 21));
        lblNodeName = new QLabel(gbNodeOperations);
        lblNodeName->setObjectName(QStringLiteral("lblNodeName"));
        lblNodeName->setGeometry(QRect(10, 30, 61, 16));
        leNode = new QLineEdit(gbNodeOperations);
        leNode->setObjectName(QStringLiteral("leNode"));
        leNode->setGeometry(QRect(80, 30, 101, 21));
        gbEdgeOpertions = new QGroupBox(centralWidget);
        gbEdgeOpertions->setObjectName(QStringLiteral("gbEdgeOpertions"));
        gbEdgeOpertions->setGeometry(QRect(210, 210, 281, 151));
        pbAddEdge = new QPushButton(gbEdgeOpertions);
        pbAddEdge->setObjectName(QStringLiteral("pbAddEdge"));
        pbAddEdge->setGeometry(QRect(100, 120, 80, 21));
        pbDeleteEdge = new QPushButton(gbEdgeOpertions);
        pbDeleteEdge->setObjectName(QStringLiteral("pbDeleteEdge"));
        pbDeleteEdge->setGeometry(QRect(190, 120, 80, 21));
        lblNodeFromName = new QLabel(gbEdgeOpertions);
        lblNodeFromName->setObjectName(QStringLiteral("lblNodeFromName"));
        lblNodeFromName->setGeometry(QRect(10, 30, 91, 16));
        leNodeFromName = new QLineEdit(gbEdgeOpertions);
        leNodeFromName->setObjectName(QStringLiteral("leNodeFromName"));
        leNodeFromName->setGeometry(QRect(100, 30, 171, 21));
        lblNodeToName = new QLabel(gbEdgeOpertions);
        lblNodeToName->setObjectName(QStringLiteral("lblNodeToName"));
        lblNodeToName->setGeometry(QRect(10, 90, 81, 16));
        leNodeToName = new QLineEdit(gbEdgeOpertions);
        leNodeToName->setObjectName(QStringLiteral("leNodeToName"));
        leNodeToName->setGeometry(QRect(100, 90, 171, 21));
        lblEdgeWeight = new QLabel(gbEdgeOpertions);
        lblEdgeWeight->setObjectName(QStringLiteral("lblEdgeWeight"));
        lblEdgeWeight->setGeometry(QRect(10, 60, 91, 16));
        leEdgeWeight = new QLineEdit(gbEdgeOpertions);
        leEdgeWeight->setObjectName(QStringLiteral("leEdgeWeight"));
        leEdgeWeight->setGeometry(QRect(100, 60, 171, 21));
        bgOther = new QGroupBox(centralWidget);
        bgOther->setObjectName(QStringLiteral("bgOther"));
        bgOther->setGeometry(QRect(500, 10, 191, 351));
        pteOther = new QPlainTextEdit(bgOther);
        pteOther->setObjectName(QStringLiteral("pteOther"));
        pteOther->setGeometry(QRect(10, 30, 171, 281));
        pbDFS = new QPushButton(bgOther);
        pbDFS->setObjectName(QStringLiteral("pbDFS"));
        pbDFS->setGeometry(QRect(10, 320, 80, 21));
        leDFSNodeFrom = new QLineEdit(bgOther);
        leDFSNodeFrom->setObjectName(QStringLiteral("leDFSNodeFrom"));
        leDFSNodeFrom->setGeometry(QRect(100, 320, 81, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 707, 20));
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
        lblGraphPower->setText(QApplication::translate("MainWindow", "Graph power:", nullptr));
        lblRadius->setText(QApplication::translate("MainWindow", "Radius:", nullptr));
        lblCircuitRank->setText(QApplication::translate("MainWindow", "Circuit rank:", nullptr));
        lblDiameter->setText(QApplication::translate("MainWindow", "Diameter:", nullptr));
        lblConnectedComponent->setText(QApplication::translate("MainWindow", "Strongly conn. comp:", nullptr));
        pbCalcMetrics->setText(QApplication::translate("MainWindow", "Evaluate", nullptr));
        lblIsTree->setText(QApplication::translate("MainWindow", "Is tree:", nullptr));
        lblIsOrientiered->setText(QApplication::translate("MainWindow", "Is orientiered:", nullptr));
        rbOrient->setText(QApplication::translate("MainWindow", "Yes", nullptr));
        rbNotOrient->setText(QApplication::translate("MainWindow", "No", nullptr));
        gbNodeOperations->setTitle(QApplication::translate("MainWindow", "Node operations", nullptr));
        pbAddNode->setText(QApplication::translate("MainWindow", "Add", nullptr));
        pbDeleteNode->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        lblNodeName->setText(QApplication::translate("MainWindow", "Node name:", nullptr));
        gbEdgeOpertions->setTitle(QApplication::translate("MainWindow", "Edge operations", nullptr));
        pbAddEdge->setText(QApplication::translate("MainWindow", "Add", nullptr));
        pbDeleteEdge->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        lblNodeFromName->setText(QApplication::translate("MainWindow", "Node-from name:", nullptr));
        lblNodeToName->setText(QApplication::translate("MainWindow", "Node-to name:", nullptr));
        lblEdgeWeight->setText(QApplication::translate("MainWindow", "Weight:", nullptr));
        bgOther->setTitle(QApplication::translate("MainWindow", "Other", nullptr));
        pbDFS->setText(QApplication::translate("MainWindow", "DFS", nullptr));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Load from...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
