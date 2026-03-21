/** @file Options.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_OPTIONS_H
#define LODESTONE_OPTIONS_H

#include "Lodestone.App/gui/options/GuiOptionRegistry.h"

#include <nlohmann/json.hpp>

namespace lodestone::app {
    class Options {
    protected:
        Options();
    public:
        static Options fromJson(const nlohmann::json &json);
        static Options fromJson(std::istream &stream);

        nlohmann::json toJson() const;

        static Options fromDefault();

        std::filesystem::path extensionsPath;

        void registerGuiOptions();

        gui::option::GuiOptionRegistry &guiOptions() {
            return this->m_guiOptions;
        }

    private:
        template <typename T>
        static void set(const nlohmann::json &json, const std::string &key, std::function<void(T)> predicate, T fallback) {
            for (auto it = json.find(key); it != json.end(); ++it) {
                predicate(static_cast<T>(it.value()));
                return;
            }

            predicate(fallback);
        }

        template <typename T>
        static void setIfNonNull(const nlohmann::json &json, const std::string &key, std::function<void(T)> predicate) {
            if (!json.contains(key)) {
                return;
            }

            const auto &v = json.at(key);
            if (v.is_null()) {
                return;
            }

            predicate(v.get<T>());
        }

        template <typename T>
        void setIfNonNull(const nlohmann::json &json, const std::string &key, T &output) const {
            if (!json.contains(key)) {
                return;
            }

            const auto &v = json.at(key);
            if (v.is_null()) {
                return;
            }

            this->setIfNonNull(v.get<T>(), output);
        }

        template <typename T>
        void setIfNonNull(std::optional<T> value, T &output) const {
            if (value.has_value()) {
                output = value.value();
            }
        }

        gui::option::GuiOptionRegistry m_guiOptions;
    };
}

#endif // LODESTONE_OPTIONS_H