#include <gtkmm.h>

class Window : public Gtk::Window {
public:
  Gtk::Box box;
  Gtk::Label first_label, last_label;
  Gtk::Entry first_entry, last_entry;
  Gtk::Button button;
  Gtk::Label label;

  Window() : box(Gtk::Orientation::ORIENTATION_VERTICAL),    
              first_label("First name"),
              last_label("Last name") {
    button.set_label("Combine names");
    button.set_sensitive(false);

    box.pack_start(first_label);
    box.pack_start(first_entry);  // Add the widget entry to box
    box.pack_start(last_label);
    box.pack_start(last_entry);  // Add the widget entry to box
    box.pack_start(button); // Add the widget button to box
    box.pack_start(label);  // Add the widget label to box

    add(box);   // Add vbox to window
    show_all(); // Show all widgets
    label.hide();

    auto update = [this]() {
      const auto first = first_entry.get_text();
      const auto last = last_entry.get_text();
      const bool ready = !first.empty() && !last.empty();

      button.set_sensitive(ready);
      if (ready) {
        label.set_text("Names combined: " + first + " " + last);
      } else {
        label.hide();
      }
    };

    first_entry.signal_changed().connect(update);
    last_entry.signal_changed().connect(update);


    first_entry.signal_activate().connect([this]() {
      label.set_text("Entry activated");
    });

    last_entry.signal_activate().connect([this]() {
      label.set_text("Entry activated");
    });

    button.signal_clicked().connect([this]() {
      label.show();
    });

    update();
  }
};

int main() {
  auto app = Gtk::Application::create();
  Window window;
  return app->run(window);
}
