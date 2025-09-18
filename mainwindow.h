// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addresswidget.h"

#include <QMainWindow>

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    // Getters for testing
    AddressWidget* getAddressWidget() const { return addressWidget; }
    QAction* getEditAction() const { return editAct; }
    QAction* getRemoveAction() const { return removeAct; }
    QAction* getAddAction() const { return addAct; }

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
    void createMenus();

    AddressWidget *addressWidget;
    QAction *editAct;
    QAction *removeAct;
    QAction *addAct;
};
//! [0]

#endif // MAINWINDOW_H
