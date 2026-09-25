/** @file LodestoneAppExtension.h
*
 * @author Zero_DSRS_VX
 * @date 7/11/26
 *
 * @device PC
 */
#ifndef LODESTONE_APP_EXTENSION_H
#define LODESTONE_APP_EXTENSION_H
#pragma once

#include <QtCore/QtPlugin>

#define LODESTONE_APP_EXTENSION_IID "io.github.team-lodestone/1.0"

namespace lodestone::common::registry {
    class Identifier;
}

class LodestoneAppExtension {
public:
    virtual ~LodestoneAppExtension() = default;

    virtual QString getIdentifier() const = 0;
    virtual QString getVersion() const = 0;
};

Q_DECLARE_INTERFACE(LodestoneAppExtension, LODESTONE_APP_EXTENSION_IID);

#endif //LODESTONE_APP_EXTENSION_H
