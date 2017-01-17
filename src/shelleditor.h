/*
 * Copyright (c) 2017 Jason Waataja
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


#ifndef SHELL_EDITOR_H
#define SHELL_EDITOR_H

#include <gtkmm.h>

#include "shellaction.h"

namespace gdfm {

class ShellEditor : public Gtk::Dialog {
public:
    ShellEditor(Gtk::Window& parent, ShellAction* action);

private:
    ShellAction* action;
    Gtk::Entry* nameEntry;
    Gtk::TreeView* commandsView;
    Gtk::Entry* commandEntry;
    Gtk::Button* removeCommandButton;

    Gtk::TreeModelColumnRecord columns;
    Glib::RefPtr<Gtk::TreeSelection> commandsSelection;
    Glib::RefPtr<Gtk::ListStore> commandsStore;
    Gtk::TreeModelColumn<Glib::ustring> commandColumn;

    void onCommandsSelectionChanged();
    void onAddCommandButtonClicked();
    void onRemoveCommandButtonClicked();
    void onResponse(int responseId);
};
} /* namespace gdfm */

#endif /* SHELL_EDITOR_H */