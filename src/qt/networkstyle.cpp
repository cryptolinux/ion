// Copyright (c) 2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The Ion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/networkstyle.h>

#include <qt/guiconstants.h>
#include <qt/guiutil.h>

#include <chainparams.h>
#include <tinyformat.h>
#include <util.h>

#include <QApplication>

static const struct {
    const char *networkId;
    const char *appName;
    const int iconColorHueShift;
    const int iconColorSaturationReduction;
    const std::string titleAddText;
} network_styles[] = {
    {"main", QAPP_APP_NAME_DEFAULT, ":/icons/bitcoin", "", ":/images/splash"},
    {"test", QAPP_APP_NAME_TESTNET, ":/icons/bitcoin_testnet", QT_TRANSLATE_NOOP("SplashScreen", "[testnet]"), ":/images/splash_testnet"},
    {"regtest", QAPP_APP_NAME_REGTEST, ":/icons/bitcoin_regtest", QT_TRANSLATE_NOOP("SplashScreen", "[regtest]"), ":/images/splash_regtest"}};
static const unsigned network_styles_count = sizeof(network_styles) / sizeof(*network_styles);

// titleAddText needs to be const char* for tr()
NetworkStyle::NetworkStyle(const QString &_appName, const int iconColorHueShift, const int iconColorSaturationReduction, const char *_titleAddText):
    appName(_appName),
    titleAddText(qApp->translate("SplashScreen", _titleAddText)),
    badgeColor(QColor(0, 141, 228)) // default badge color is the original Dash's blue, regardless of the current theme
{
    // Allow for separate UI settings for testnets
    QApplication::setApplicationName(appName);
    // Make sure settings migrated properly
    GUIUtil::migrateQtSettings();
    // load pixmap
    QPixmap appIconPixmap(":/icons/bitcoin");

    if(iconColorHueShift != 0 && iconColorSaturationReduction != 0)
    {
        // generate QImage from QPixmap
        QImage appIconImg = appIconPixmap.toImage();
        rotateColors(appIconImg, iconColorHueShift, iconColorSaturationReduction);
        //convert back to QPixmap
#if QT_VERSION >= 0x040700
        appIconPixmap.convertFromImage(appIconImg);
#else
        appIconPixmap = QPixmap::fromImage(appIconImg);
#endif
        // tweak badge color
        rotateColor(badgeColor, iconColorHueShift, iconColorSaturationReduction);
    }

    appIcon             = QIcon(appIconPixmap);
    trayAndWindowIcon   = QIcon(appIconPixmap.scaled(QSize(256,256)));
    splashImage         = QPixmap(":/images/splash");
}

const NetworkStyle *NetworkStyle::instantiate(const QString &networkId)
{
    for (unsigned x=0; x<network_styles_count; ++x)
    {
        if (networkId == network_styles[x].networkId)
        {
            std::string appName = network_styles[x].appName;
            std::string titleAddText = network_styles[x].titleAddText;

            if (networkId == QString(CBaseChainParams::DEVNET.c_str())) {
                appName = strprintf(appName, gArgs.GetDevNetName());
                titleAddText = strprintf(titleAddText, gArgs.GetDevNetName());
            }

            return new NetworkStyle(
                    appName.c_str(),
                    network_styles[x].iconColorHueShift,
                    network_styles[x].iconColorSaturationReduction,
                    titleAddText.c_str());
        }
    }
    return 0;
}
