/** @file LodestoneJavaPlugin.cpp
*
 * @author Zero_DSRS_VX
 * @date 7/11/26
 *
 * @device PC
 */
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
