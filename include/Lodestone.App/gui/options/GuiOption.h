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
        virtual ~IGuiOption() = default;

        explicit constexpr IGuiOption(const std::string &name, const std::string &description) : m_displayName(name), m_description(description) {};

        template <typename T> GuiOption<T> *asOptionType() {
            return dynamic_cast<GuiOption<T> *>(this);
        }

        const std::string &displayName() const {
            return this->m_displayName;
        }

        const std::string &description() const {
            return this->m_description;
        }

        virtual QWidget *getWidget(QWidget *parent = nullptr) = 0;

    protected:
        const std::string m_displayName;
        const std::string m_description;
    };

    template <typename T>
    class GuiOption : public IGuiOption {
    public:
        constexpr GuiOption(const std::string &name, const std::string &description, std::function<T()> getter, std::function<void(T)> setter) : IGuiOption(name, description), m_getter(getter), m_setter(setter) {}

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

    private:
        const std::function<T()> m_getter;
        const std::function<void(T)> m_setter;
    };

    template <typename T>
    class GuiOptionWithPresets : public GuiOption<T> {
    public:
        constexpr GuiOptionWithPresets(const std::string &name, const std::string &description, const std::function<T()> &getter, const std::function<void(T)> &setter, const std::initializer_list<T> &presets) : GuiOption<T>(name, description, getter, setter), m_presets(presets) {}

        const std::vector<T> &presets() const {
            return this->m_presets;
        }
    protected:
        const std::vector<T> m_presets;
    };
}

#endif // LODESTONE_GUIOPTION_H