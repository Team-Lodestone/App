//
// Created by zero on 7/11/26.
//

#include "LodestoneJavaExt/LodestoneJavaPlugin.h"

LodestoneJavaPlugin::LodestoneJavaPlugin() {
    qInfo() << "LodestoneJavaPlugin initialized";
}

QString LodestoneJavaPlugin::getIdentifier() const {
    return "lodestone:minecraft/java";
}

QString LodestoneJavaPlugin::getVersion() const {
    return "v1.0.0";
}
