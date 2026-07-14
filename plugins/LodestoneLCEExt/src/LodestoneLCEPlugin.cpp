//
// Created by zero on 7/12/26.
//

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