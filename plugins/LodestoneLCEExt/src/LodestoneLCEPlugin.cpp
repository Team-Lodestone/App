/** @file LodestoneLCEPlugin.cpp
 *
 * @author Zero_DSRS_VX
 * @date 7/12/26
 *
 * @device PC
 */
#include "LodestoneLCEExt/LodestoneLCEPlugin.h"

LodestoneLCEPlugin::LodestoneLCEPlugin() {
    qInfo() << "LodestoneLCEPlugin initialized";
}

QString LodestoneLCEPlugin::getIdentifier() const {
    return "lodestone:minecraft/legacy_console";
}

QString LodestoneLCEPlugin::getVersion() const {
    return "v1.0.0";
}