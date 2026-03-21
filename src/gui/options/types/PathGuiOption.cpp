/** @file PathGuiOption.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/options/types/PathGuiOption.h"

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/widgets/OptionWidget.h"
#include <QComboBox>
#include <QLineEdit>
#include <ranges>

namespace lodestone::app::gui::option::types {
    QWidget *PathGuiOption::getWidget(QWidget *parent) {
        widgets::OptionWidget *optionWidget = new widgets::OptionWidget(this, parent);

        QVBoxLayout *layout = optionWidget->mainLayout();

        QStringList presetsList;
        presetsList.reserve(this->m_presets.size());

        std::ranges::transform(this->m_presets, std::back_inserter(presetsList), [](const std::filesystem::path &path) {
            return QString::fromStdString(path.generic_string());
        });

        QComboBox *comboBox = new QComboBox();
        comboBox->addItems(presetsList);
        comboBox->setEditable(true);
        comboBox->setInsertPolicy(QComboBox::NoInsert);

        comboBox->setCurrentText(QString::fromStdString(this->get().generic_string()));

        comboBox->connect(comboBox->lineEdit(), &QLineEdit::editingFinished, optionWidget, [comboBox, this, optionWidget] {
            const QString path = comboBox->currentText().trimmed();

            if (path.isEmpty()) {
                return;
            }

            std::filesystem::path p = path.toStdString();
            p.make_preferred();

            if (std::filesystem::exists(p) && !std::filesystem::is_directory(p)) {
                optionWidget->setErrorMessage("Path is not a directory");
                optionWidget->setErrorVisible(true);
                return;
            }

            optionWidget->setErrorVisible(false);

            this->set(p);
        });

        layout->addWidget(comboBox);

        return optionWidget;
    }
}