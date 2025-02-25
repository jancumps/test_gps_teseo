#include <gtest/gtest.h>
#include <string>
import teseo;

const size_t NMEA_MAX_REPLIES = 7;

class teseoTest : public testing::Test {
protected:
    teseoTest() : count(0) {}
    void SetUp() override {
        o.writer().set([](const std::string& s) -> void { write(s); });
        o.reader().set([](std::string& s) -> void { read(s); });
        o.resetter().set([]() -> void { reset(); });
    }
    static void write(const std::string& s) {        
    }
    static void read(std::string& s) {
    }
    static void reset() {
    }
    bool test_parse_multiline_reply(const teseo::nmea_rr& command) {
        return o.parse_multiline_reply(replies, reply, count, command);
    }

    teseo::teseo o;
    std::string reply;
    std::array<std::string, NMEA_MAX_REPLIES> replies;
    unsigned int count;
};

TEST_F(teseoTest, parseMultilineReply) {
    teseo::nmea_rr command("testcommand", "TST");
    reply = "XXXTST\r\nXXXTST\r\ntestcommand\r\n";
    EXPECT_TRUE(test_parse_multiline_reply(command));
    EXPECT_EQ(count, 2);
    EXPECT_STREQ(replies[0].c_str(), "XXXTST\r\n");
    EXPECT_STREQ(replies[1].c_str(), "XXXTST\r\n");
}

TEST_F(teseoTest, parseSinglelineReply) {
    teseo::nmea_rr command("testcommand", "TST");
    reply = "XXXTST\r\ntestcommand\r\n";
    EXPECT_TRUE(test_parse_multiline_reply(command));
    EXPECT_EQ(count, 1);
    EXPECT_STREQ(replies[0].c_str(), "XXXTST\r\n");
}

TEST_F(teseoTest, callbacksSet) {
    EXPECT_FALSE(o.writer().is_set());
    EXPECT_TRUE(o.reader().is_set());
    EXPECT_TRUE(o.resetter().is_set());
}