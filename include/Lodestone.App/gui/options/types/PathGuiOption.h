/** @file PathGuiOption.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_PATHGUIOPTION_H
#define LODESTONE_PATHGUIOPTION_H
#include "Lodestone.App/gui/options/GuiOption.h"

#include <QComboBox>
#include <QLabel>
#include <filesystem>

namespace lodestone::app::gui::option::types {
    class PathGuiOption : public GuiOptionWithPresets<std::filesystem::path> {
    public:
        constexpr PathGuiOption(const std::string &name, const std::string &description, const std::function<std::filesystem::path()> &getter,
            const std::function<void(std::filesystem::path)> &setter, const std::initializer_list<std::filesystem::path> &presets)
            : GuiOptionWithPresets(name, description, getter, setter, presets) {
        }

        QWidget *getWidget(QWidget *parent = nullptr) override;
    };
}

#endif // LODESTONE_PATHGUIOPTION_H