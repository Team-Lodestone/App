/** @file Environment.cpp
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/util/Environment.h"

#include <QStandardPaths>
#include <qcoreapplication.h>

namespace lodestone::app::util {
    // HACK TO GET AROUND https://forum.qt.io/post/812515
    std::filesystem::path Environment::getStorageDirectory() {
        return std::filesystem::path(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toUtf8().data()).make_preferred();
    }

    std::filesystem::path Environment::getConfigDirectory() {
        return std::filesystem::path(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).toUtf8().data()).make_preferred();
    }

    std::filesystem::path Environment::getCurrentDirectory() {
        return std::filesystem::path(QCoreApplication::applicationDirPath().toUtf8().data()).make_preferred();
    }
}