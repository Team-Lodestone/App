/** @file GuiOption.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_GUIOPTION_H
#define LODESTONE_GUIOPTION_H
#include <QWidget>
#include <functional>
#include <string>

namespace lodestone::app::gui::option {
    template <typename T>
    class GuiOption;

    class IGuiOption {
    public:
        explicit constexpr IGuiOption(const std::string &name) : m_displayName(name) {};

        template <typename T> GuiOption<T> *asOptionType() {
            return dynamic_cast<GuiOption<T> *>(this);
        }

        const std::string &displayName() const {
            return this->m_displayName;
        }

        // virtual QWidget *getWidget() = 0;

    protected:
        const std::string m_displayName;
    };

    //TODO for tomorrow: keep getWidget pure, instantiate per type we want to implement our options widget for
    // so I can implement for T = std::string as a textbox
    // and then move initializer_list there
    template <typename T>
    class GuiOption : public IGuiOption {
    public:
        constexpr GuiOption(const std::string &name, std::function<T()> getter, std::function<void(T)> setter, std::initializer_list<T> presets = {}) : IGuiOption(name), m_getter(getter), m_setter(setter), m_presets(presets) {}

        T operator()() {
            return this->get();
        }

        void operator()(T value) {
            this->set(value);
        }

        T get() {
            return this->m_getter();
        }

        void set(T value) {
            this->m_setter(value);
        }

        const std::vector<T> &presets() const {
            return this->m_presets;
        }

    private:
        const std::function<T()> m_getter;
        const std::function<void(T)> m_setter;
        const std::vector<T> m_presets;
    };
}

#endif // LODESTONE_GUIOPTION_H