// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2017-2018 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPTIONSDIALOG_H
#define BITCOIN_QT_OPTIONSDIALOG_H

#include <QButtonGroup>
#include <QDialog>
#include <QValidator>

class AppearanceWidget;
class OptionsModel;
class QValidatedLineEdit;

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

namespace Ui {
class OptionsDialog;
}

/** Proxy address widget validator, checks for a valid proxy address.
 */
class ProxyAddressValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ProxyAddressValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Preferences dialog. */
class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent, bool enableWallet);
    ~OptionsDialog();

    void setModel(OptionsModel *model);
    void setMapper();
    void setCurrentIndex(int index);

private Q_SLOTS:
    /** custom tab buttons clicked */
    void showPage(int index);
    /* set OK button state (enabled / disabled) */
    void setOkButtonState(bool fState);
    void on_resetButton_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    
    void on_hideTrayIcon_stateChanged(int fState);

    void updateHideOrphans(bool fHide);

    void updateHideOrphans(bool fHide);

    void showRestartWarning(bool fPersistent = false);
    void clearStatusLabel();
    void updateProxyValidationState();
    /* query the networks, for which the default proxy is used */
    void updateDefaultProxyNets();

    void updatePrivateSendVisibility();

    void updateWidth();

Q_SIGNALS:
    void appearanceChanged();
    void proxyIpChecks(QValidatedLineEdit *pUiProxyIp, int nProxyPort);

private:
    Ui::OptionsDialog *ui;
    OptionsModel *model;
    QDataWidgetMapper *mapper;
    QButtonGroup pageButtons;
    QString previousTheme;
    AppearanceWidget* appearance;
    bool fPrivateSendEnabledPrev{false};

    void showEvent(QShowEvent* event) override;
};

#endif // BITCOIN_QT_OPTIONSDIALOG_H
