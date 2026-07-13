/** @file EmscriptenHooks.h
*
 * @author Zero_DSRS_VX
 * @date 7/13/26
 *
 * @device PC
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */

#ifndef LODESTONE_EMSCRIPTEN_HOOKS_H
#define LODESTONE_EMSCRIPTEN_HOOKS_H

#include <qplugin.h>

#include "Lodestone.App/LodestoneApp.h"

#ifdef __EMSCRIPTEN__

// Import plugins statically
#if LODESTONE_APP_BUILD_JAVA_EXT
    #include "Lodestone.Minecraft.Java/LodestoneJava.h"
    Q_IMPORT_PLUGIN(LodestoneJavaPlugin)
#endif

#if LODESTONE_APP_BUILD_LCE_EXT
    #include "Lodestone.Minecraft.Console/LodestoneLce.h"
    Q_IMPORT_PLUGIN(LodestoneLCEPlugin)
#endif

#endif


namespace lodestone::app {
        class EmscriptenHooks {
        public:
            static void loadStaticExtensions(LodestoneApp *app);
        };
}

#endif //LODESTONE_EMSCRIPTEN_HOOKS_H
