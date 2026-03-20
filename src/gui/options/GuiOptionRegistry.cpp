/** @file GuiOptionRegistry.cpp
 *
 * @author DexrnZacAttack
 * @date 3/19/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/options/GuiOptionRegistry.h"

namespace lodestone::app::gui::option {
    void GuiOptionRegistry::put(const common::registry::Identifier &id, std::unique_ptr<IGuiOption> option) {
        if (this->m_registry.contains(id))
            return;

        this->m_registry.emplace(id, std::move(option));

        this->objectRegisteredEvent.notify(id);
    }

    void GuiOptionRegistry::put(const common::registry::Identifier &id, IGuiOption *option) {
        this->put(id, std::unique_ptr<IGuiOption>(option));
    }

    const IGuiOption * GuiOptionRegistry::get(const common::registry::Identifier &id) const {
        if (const auto it = m_registry.find(id); it != m_registry.end())
            return it->second.get();

        return nullptr;
    }

    const std::unordered_map<common::registry::Identifier, std::unique_ptr<IGuiOption>> &GuiOptionRegistry::registeredOptions() {
        return this->m_registry;
    }
}