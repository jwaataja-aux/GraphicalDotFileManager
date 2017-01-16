/*
 * Copyright (c) 2016 Jason Waataja
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "module.h"

#include <err.h>

namespace gdfm {

Module::Module() : name(DEFAULT_MODULE_NAMES)
{
}

Module::Module(const std::string& name) : name(name)
{
}

const std::string&
Module::getName() const
{
    return name;
}

void
Module::setName(const std::string& name)
{
    this->name = name;
}

bool
Module::install(const std::string& sourceDirectory) const
{
    for (const auto& file : files) {
        std::shared_ptr<InstallAction> installAction =
            file.createInstallAction(sourceDirectory);
        if (installAction->performAction()) {
            warnx("Failed to perform action \"%s\".",
                installAction->getName().c_str());
            return false;
        }
    }
    for (const auto& action : installActions) {
        bool status = action->performAction();
        if (!status) {
            warnx(
                "Failed to perform action \"%s\".", action->getName().c_str());
            return false;
        }
    }
    return true;
}

bool
Module::uninstall(const std::string& sourceDirectory) const
{
    for (const auto& file : files) {
        std::shared_ptr<RemoveAction> uninstallAction =
            file.createUninstallAction();
        if (uninstallAction->performAction()) {
            warnx("Failed to perform action \"%s\".",
                uninstallAction->getName().c_str());
            return false;
        }
    }
    for (const auto& action : uninstallActions) {
        bool status = action->performAction();
        if (!status) {
            warnx(
                "Failed to perform action \"%s\".", action->getName().c_str());
            return false;
        }
    }
    return true;
}


bool
Module::update(const std::string& sourceDirectory) const
{
    for (const auto& file : files) {
        std::shared_ptr<FileCheckAction> updateAction =
            file.createUpdateAction(sourceDirectory);
        if (!updateAction->performAction()) {
            warnx("Failed to perform action \"%s\".",
                updateAction->getName().c_str());
            return false;
        }
    }
    for (const auto& action : updateActions) {
        bool status = action->performAction();
        if (!status) {
            warnx(
                "Failed to perform action \"%s\".", action->getName().c_str());
            return false;
        }
    }
    return true;
}

void
Module::addInstallAction(std::shared_ptr<ModuleAction> action)
{
    installActions.push_back(action);
}

void
Module::addUninstallAction(std::shared_ptr<ModuleAction> action)
{
    uninstallActions.push_back(action);
}

void
Module::addUpdateAction(std::shared_ptr<ModuleAction> action)
{
    updateActions.push_back(action);
}

const std::vector<std::shared_ptr<ModuleAction>>&
Module::getInstallActions() const
{
    return installActions;
}

const std::vector<std::shared_ptr<ModuleAction>>&
Module::getUninstallActions() const
{
    return uninstallActions;
}

const std::vector<std::shared_ptr<ModuleAction>>&
Module::getUpdateActions() const
{
    return updateActions;
}

void
Module::addFile(const std::string& filename)
{
    files.push_back(ModuleFile(filename));
}

void
Module::addFile(
    const std::string& filename, const std::string& destinationDirectory)
{
    files.push_back(ModuleFile(filename, destinationDirectory));
}

void
Module::addFile(const std::string& filename,
    const std::string& destinationDirectory,
    const std::string& destinationFilename)
{
    files.push_back(
        ModuleFile(filename, destinationDirectory, destinationFilename));
}

const std::vector<ModuleFile>
Module::getFiles() const
{
    return files;
}
} /* namespace gdfm */
