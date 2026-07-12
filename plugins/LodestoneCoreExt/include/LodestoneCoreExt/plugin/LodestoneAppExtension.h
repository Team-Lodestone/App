//
// Created by zero on 7/11/26.
//

#ifndef LODESTONE_APP_EXTENSION_H
#define LODESTONE_APP_EXTENSION_H
#pragma once

#include <QtCore/QtPlugin>

#define LODESTONE_APP_EXTENSION_IID "io.github.team-lodestone/1.0"

class LodestoneAppExtension {
public:
    virtual ~LodestoneAppExtension() = default;
};

Q_DECLARE_INTERFACE(LodestoneAppExtension, LODESTONE_APP_EXTENSION_IID);

#endif //LODESTONE_APP_EXTENSION_H
