/** @file GuiOptionRegistry.h
 *
 * @author DexrnZacAttack
 * @date 3/19/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_GUIOPTIONREGISTRY_H
#define LODESTONE_GUIOPTIONREGISTRY_H
#include "Lodestone.App/gui/options/GuiOption.h"
#include "Lodestone.Common/registry/Identifier.h"
#include "Lodestone.Conversion/registry/SingletonRegistry.h"

#include <memory>
#include <unordered_map>

namespace lodestone::app::gui::option {
    class GuiOptionRegistry {
    public:
        void put(const common::registry::Identifier &id, std::unique_ptr<IGuiOption> option);
        void put(const common::registry::Identifier &id, IGuiOption *option);

        template <typename T>
        void putOption(const common::registry::Identifier &id, GuiOption<T> *option) {
            this->put(id, std::unique_ptr<GuiOption<T>>(option));
        }

        template <typename T>
        void putOption(const common::registry::Identifier &id, std::unique_ptr<GuiOption<T>> option) {
            this->put(id, std::move(option));
        }

        template <typename T, typename... Args>
        void putOption(const common::registry::Identifier &id, Args&&... args) {
            this->put(id, std::make_unique<GuiOption<T>>(std::forward<Args>(args)...));
        }

        template <typename T>
        GuiOption<T> *getOption(const common::registry::Identifier &identifier) {
            return this->get(identifier)->asOptionType<T>();
        }

        const IGuiOption *get(const common::registry::Identifier &id) const;

        const std::unordered_map<common::registry::Identifier, std::unique_ptr<IGuiOption>> &registeredOptions();

        common::event::Event<common::registry::Identifier> objectRegisteredEvent;
    private:
        std::unordered_map<common::registry::Identifier,
            std::unique_ptr<IGuiOption>>
            m_registry;
    };
}

#endif // LODESTONE_GUIOPTIONREGISTRY_H