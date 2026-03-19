/** @file Options.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_OPTIONS_H
#define LODESTONE_OPTIONS_H

#include <nlohmann/json.hpp>

namespace lodestone::app {
    class Options {
    public:
        Options();

        static Options fromJson(const nlohmann::json &json);
        static Options fromJson(std::istream &stream);

        nlohmann::json toJson() const;

        static Options fromDefault();

        std::filesystem::path extensionsPath;

    private:
        template <typename T>
        static void set(const nlohmann::json &json, const std::string &key, std::function<void(T)> predicate, T fallback) {
            for (auto it = json.find(key); it != json.end(); ++it) {
                if (typeid(it.value().type()) == typeid(T)) {
                    predicate(static_cast<T>(it.value()));
                    return;
                }
            }

            predicate(fallback);
        }

        template <typename T>
        static void setIfNonNull(const nlohmann::json &json, const std::string &key, std::function<void(T)> predicate) {
            for (auto it = json.find(key); it != json.end(); ++it) {
                if (typeid(it.value().type()) == typeid(T)) {
                    predicate(static_cast<T>(it.value()));
                }
            }
        }

        template <typename T>
        void setIfNonNull(const nlohmann::json &json, const std::string &key, T &output) const {
            for (auto it = json.find(key); it != json.end(); ++it) {
                if (typeid(it.value().type()) == typeid(T)) {
                    this->setIfNonNull<T>(it.value().get<T>(), output);
                }
            }
        }

        template <typename T>
        void setIfNonNull(std::optional<T> value, T &output) const {
            if (value.has_value()) {
                output = value.value();
            }
        }
    };
}

#endif // LODESTONE_OPTIONS_H