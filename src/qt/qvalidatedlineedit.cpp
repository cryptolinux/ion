// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/qvalidatedlineedit.h>

#include <qt/bitcoinaddressvalidator.h>
#include <qt/guiutil.h>

QValidatedLineEdit::QValidatedLineEdit(QWidget *parent) :
    QLineEdit(parent),
    valid(true),
    checkValidator(0)
{
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(markValid()));
}

void QValidatedLineEdit::setValid(bool _valid)
{
    if(_valid == this->valid)
    {
        return;
    }

    if(_valid)
    {
        setStyleSheet("");
    }
    else
    {
        setStyleSheet(GUIUtil::getThemedStyleQString(GUIUtil::ThemedStyle::TS_INVALID));
    }
    this->valid = _valid;
}

void QValidatedLineEdit::focusInEvent(QFocusEvent *evt)
{
    // Clear invalid flag on focus
    setValid(true);

    QLineEdit::focusInEvent(evt);
}

void QValidatedLineEdit::focusOutEvent(QFocusEvent *evt)
{
    checkValidity();

    QLineEdit::focusOutEvent(evt);
}

void QValidatedLineEdit::markValid()
{
    // As long as a user is typing ensure we display state as valid
    setValid(true);
}

void QValidatedLineEdit::clear()
{
    setValid(true);
    QLineEdit::clear();
}

void QValidatedLineEdit::setEnabled(bool enabled)
{
    if (!enabled)
    {
        // A disabled QValidatedLineEdit should be marked valid
        setValid(true);
    }
    else
    {
        // Recheck validity when QValidatedLineEdit gets enabled
        checkValidity();
    }

    QLineEdit::setEnabled(enabled);
}

void QValidatedLineEdit::checkValidity()
{
    if (text().isEmpty())
    {
        setValid(true);
    }
    else if (hasAcceptableInput())
    {
        setValid(true);

        // Check contents on focus out
        if (checkValidator)
        {
            QString address = text();
            int pos = 0;
            if (checkValidator->validate(address, pos) == QValidator::Acceptable)
                setValid(true);
            else
                setValid(false);
        }
    }
    else
        setValid(false);

    Q_EMIT validationDidChange(this);
}

void QValidatedLineEdit::setCheckValidator(const QValidator *v)
{
    checkValidator = v;
}

bool QValidatedLineEdit::isValid()
{
    // use checkValidator in case the QValidatedLineEdit is disabled
    if (checkValidator)
    {
        QString address = text();
        int pos = 0;
        if (checkValidator->validate(address, pos) == QValidator::Acceptable)
            return true;
    }

    return valid;
}
