module;
#include <string_view>
export module test_module;

export namespace test_module {

class TestClass {
public:
  bool match(const std::string_view& sv);
};

} // namespace test_module