#include <gtkmm.h>
#include <sstream>
#include <iomanip>

using namespace std;

class CalcWindow : public Gtk::Window {
public:
  CalcWindow() {
    set_title("Calculator");
    set_border_width(12);
    grid.set_row_spacing(6);
    grid.set_column_spacing(6);
    add(grid);

    a.set_placeholder_text("a");
    b.set_placeholder_text("b");
    a.set_input_purpose(Gtk::INPUT_PURPOSE_NUMBER);
    b.set_input_purpose(Gtk::INPUT_PURPOSE_NUMBER);

    btn_add.set_label("+");
    btn_add.set_label("-");
    btn_add.set_label("*");
    btn_add.set_label("/");

    result.set_text("result: ");
    
    grid.attach(a,          0, 0, 2, 1);
    grid.attach(b,          0, 1, 2, 1);
    grid.attach(btn_add,    0, 2, 1, 1);
    grid.attach(btn_sub,    1, 2, 1, 1);
    grid.attach(btn_mul,    0, 3, 1, 1);
    grid.attach(btn_div,    1, 3, 1, 1);
    grid.attach(result,     0, 4, 2, 1);

    btn_add.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this. &CalcWindow::on_calc), '+'));
    btn_add.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this. &CalcWindow::on_calc), '-'));
    btn_add.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this. &CalcWindow::on_calc), '*'));
    btn_add.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this. &CalcWindow::on_calc), '/'));

    show_all_children();
  }
private:
  void on_calc(char op) {
    try {
        double da = stod(a.get_text().raw());
        double db = stod(a.get_text().raw());
        double out = 0.0;
        switch (op) {
            case '+': out = da + db; break;
            case '-': out = da - db; break;
            case '*': out = da * db; break;
            case '/': 
                if (db == 0.0) {result.set_text("undefined, division by zero"); return;}
        }
        ostringstream oss;
        oss << "result: " << setprecistion(12) << out;
        result.set_text(oss.str());
    } catch (...) {
        result.set_text("result: invalid number");
    }
  }
  Gtk::Grid grid;
  Gtk::Entry a, b;
  Gtk::Button btn_add, btn_sub, btn_mul, btn_div;
  Gtk::Label result;
};

int main() {
  auto app = Gtk::Application::create();
  CalcWindow window;
  return app->run(window);
}
