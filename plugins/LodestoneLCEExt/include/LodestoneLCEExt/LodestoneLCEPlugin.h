//
// Created by zero on 7/12/26.
//

#ifndef LODESTONE_LCE_PLUGIN_H
#define LODESTONE_LCE_PLUGIN_H
#pragma once

#include <LodestoneCoreExt/plugin/LodestoneAppExtension.h>

#include <QtCore/QObject>
#include <QString>
#include <QtCore/QtPlugin>

class LodestoneLCEPlugin : public QObject, public LodestoneAppExtension {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID LODESTONE_APP_EXTENSION_IID FILE "../rsrc/plugin_metadata.json")
    Q_INTERFACES(LodestoneAppExtension)

public:
    LodestoneLCEPlugin();

    ~LodestoneLCEPlugin() override = default;
};

#endif //LODESTONE_LCE_PLUGIN_H
