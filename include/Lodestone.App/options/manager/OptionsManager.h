/** @file OptionsManager.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_OPTIONSMANAGER_H
#define LODESTONE_OPTIONSMANAGER_H
#include "Lodestone.App/Options.h"
#include "Lodestone.Common/event/Event.h"

namespace lodestone::app::options::manager {
    class OptionsManager {
    public:
        virtual ~OptionsManager() = default;

        virtual void load() = 0;
        virtual void save() = 0;
        virtual void backup() = 0;

        Options &options() {
            return this->m_options;
        }

        common::event::Event<> optionsLoadedEvent;
        common::event::Event<> optionsSavedEvent;
    protected:
        Options m_options = Options::fromDefault();
    };
}

#endif // LODESTONE_OPTIONSMANAGER_H