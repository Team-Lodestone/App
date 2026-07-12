//
// Created by zero on 7/11/26.
//

#ifndef LODESTONE_JAVA_PLUGIN_H
#define LODESTONE_JAVA_PLUGIN_H
#pragma once

#include <LodestoneCoreExt/plugin/LodestoneAppExtension.h>

#include <QtCore/QObject>
#include <QString>
#include <QtCore/QtPlugin>

class LodestoneJavaPlugin : public QObject, public LodestoneAppExtension {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID LODESTONE_APP_EXTENSION_IID FILE "../rsrc/plugin_metadata.json")
    Q_INTERFACES(LodestoneAppExtension)

public:
    LodestoneJavaPlugin();

    ~LodestoneJavaPlugin() override = default;
};

#endif //LODESTONE_JAVA_PLUGIN_H
