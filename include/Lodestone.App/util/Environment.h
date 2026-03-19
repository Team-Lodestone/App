/** @file Environment.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_ENVIRONMENT_H
#define LODESTONE_ENVIRONMENT_H
#include <filesystem>

namespace lodestone::app::util {
    class Environment {
    public:
        static std::filesystem::path getStorageDirectory();

        static std::filesystem::path getConfigDirectory();

        static std::filesystem::path getCurrentDirectory();
    };
}

#endif // LODESTONE_ENVIRONMENT_H