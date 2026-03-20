/** @file Options.cpp
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/Options.h"

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/options/GuiOptionRegistry.h"
#include "Lodestone.App/util/Environment.h"

#include <qcoreapplication.h>
#include <QStandardPaths>

namespace lodestone::app {
    Options::Options() {
#ifndef __APPLE__
        this->extensionsPath = util::Environment::getCurrentDirectory() / "extensions";
#else
        this->extensionsPath = util::Environment::getStorageDirectory() / "extensions";
#endif

        this->registerGuiOptions();
    }

    Options Options::fromJson(const nlohmann::json &json) {
        Options opt = Options::fromDefault();

        opt.setIfNonNull<std::string>(json, "extensionDirectory", [&opt](const std::string &path) {
            opt.extensionsPath = path;
        });

        return opt;
    }

    Options Options::fromJson(std::istream &stream) {
        return Options::fromJson(nlohmann::json::parse(stream));
    }

    nlohmann::json Options::toJson() const {
        nlohmann::json json;

        json["version"] = LodestoneApp::VERSION.toVersionString();
        json["extensionDirectory"] = this->extensionsPath.string();

        return json;
    }

    Options Options::fromDefault() {
        return Options();
    }

    void Options::registerGuiOptions() {
        this->m_guiOptions.putOption(common::registry::Identifier {"lodestone", "app/options/extension_directory"},
                new gui::option::GuiOption<std::filesystem::path> {
                    "Extensions Directory",
                    [this]() -> std::filesystem::path {
                        return this->extensionsPath;
                    },
                    [this](const std::filesystem::path &value) {
                        this->extensionsPath = value;
                    },
                    {
                        std::filesystem::path("placeholder")
                    }
                }
        );
    }
}