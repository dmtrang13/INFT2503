#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct BuildSystem {
  virtual ~BuildSystem() = default;
  virtual string build_cmd() const = 0;
};

struct CMake : BuildSystem {
  string build_cmd() const override {
    return "cmake --build .";
  }
};

struct Meson : BuildSystem {
  string build_cmd() const override {
    return "meson compile -C .";
  }
};

struct Cargo : BuildSystem {
  string build_cmd() const override {
    return "cargo build";
  }
};

struct ProgrammingLanguage {
virtual ~ProgrammingLanguage() = default;
virtual string print_line(const string& msg) const = 0;
virtual string for_each(const string& elem, const string& container) const = 0;
virtual string build(const string& dir = "build") const = 0;
};

struct Cpp : ProgrammingLanguage {
  explicit Cpp(unique_ptr<BuildSystem> bs = make_unique<CMake>()) : bs_(move(bs)) {}
  string print_line(const string& msg) const override {
    return "cout << \"" + msg + "\" << endl;";
  }

  string for_each(const string& e, const string& vec) const override {
    return "for(auto &" + e + ":" +  vec + ") {}";
  }
  
  string build(const string& dir = "build") const override {
    return bs_->build_cmd();
  }

private:
  unique_ptr<BuildSystem> bs_;
};

struct Rust : ProgrammingLanguage {
  explicit Rust(unique_ptr<BuildSystem> bs = make_unique<Cargo>()) : bs_(move(bs)) {}
  string print_line(const string& msg) const override {
    return "println!(\"" + msg + "\");";
  }

  string for_each(const string& e, const string& vec) const override {
    return "for " + e + "in &" + vec + "{}";
  }

  string build(const string& dir = "build") const override {
    return bs_->build_cmd();
  }

private:
  unique_ptr<BuildSystem> bs_;
};
//a)

int main() {
    vector<unique_ptr<ProgrammingLanguage>> programming_languages;
    // Uncommenting the following line should cause compilation error:
    // programming_languages.emplace_back(make_unique<ProgrammingLanguage>());
    programming_languages.emplace_back(make_unique<Cpp>());
    programming_languages.emplace_back(make_unique<Rust>());

    

    for (auto &programming_language : programming_languages) {
    cout << programming_language->print_line("Hello World") << endl;
    cout << programming_language->for_each("e", "vec") << endl
        << endl;
    }

    programming_languages.clear();

    //b
    //vector<unique_ptr<ProgrammingLanguage>> programming_languages;
    programming_languages.emplace_back(make_unique<Cpp>(make_unique<CMake>()));
    programming_languages.emplace_back(make_unique<Cpp>(make_unique<Meson>()));
    programming_languages.emplace_back(make_unique<Rust>(make_unique<Cargo>()));


    for (auto &programming_language : programming_languages) {
      cout << programming_language->build() << endl;
    }

    return 0;
}



