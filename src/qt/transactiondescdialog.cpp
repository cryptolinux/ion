// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/guiutil.h>
#include <qt/transactiondescdialog.h>
#include <qt/forms/ui_transactiondescdialog.h>

#include <qt/transactiontablemodel.h>

#include <QModelIndex>
#include <QSettings>
#include <QString>

TransactionDescDialog::TransactionDescDialog(const QModelIndex& idx, QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
                                                                                        ui(new Ui::TransactionDescDialog)
{
    ui->setupUi(this);
    GUIUtil::updateFonts();
    setWindowTitle(tr("Details for %1").arg(idx.data(TransactionTableModel::TxIDRole).toString()));
    QString desc = idx.data(TransactionTableModel::LongDescriptionRole).toString();
    ui->detailText->setHtml(desc);
}

TransactionDescDialog::~TransactionDescDialog()
{
    delete ui;
}
