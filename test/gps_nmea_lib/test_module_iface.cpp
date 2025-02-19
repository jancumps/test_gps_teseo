module;
#include <string>
#include <string_view>
export module test_module;

export namespace test_module {

class TestClass {
public:
  TestClass() : match_string() {}
  bool match(const std::string_view& sv);
  void set_match_string(const std::string& s) {
    match_string = s;
  }

private:
  std::string match_string;
};

} // namespace test_module