/** @file EmscriptenHooks.cpp
*
 * @author Zero_DSRS_VX
 * @date 7/13/26
 *
 * @device PC
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */

#include "Lodestone.App/EmscriptenHooks.h"

#include <Lodestone.Core/loader/StaticExtensionLoader.h>

void lodestone::app::EmscriptenHooks::loadStaticExtensions(LodestoneApp *app) {
    auto staticLoader = core::loader::StaticExtensionLoader(app->core());

    staticLoader.extensionLoadingEvent += [](common::event::Cancellable &/*cancellable*/, const std::filesystem::path &p) {
        std::println("Initializing extension '{}'", p.generic_string());
    };

    staticLoader.extensionLoadedEvent += [app](const core::LodestoneExtension *ext) {
        std::println("Initialized extension '{}' {}", ext->getIdentifier(), ext->getVersion().toString());
        emit app->extensionInitialized(ext);
    };

#if LODESTONE_APP_BUILD_JAVA_EXT
    staticLoader.loadExtension(minecraft::java::LodestoneJava::getInstance());
#endif

#if LODESTONE_APP_BUILD_LCE_EXT
    staticLoader.loadExtension(minecraft::console::LodestoneLCE::getInstance());
#endif

    staticLoader.load();
}
