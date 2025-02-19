module;
#include <string_view>
module test_module;

namespace test_module {
bool TestClass::match(const std::string_view& sv) {
    using std::operator""sv;
    return (match_string.compare(sv) == 0);    
}

} // namespace test_module