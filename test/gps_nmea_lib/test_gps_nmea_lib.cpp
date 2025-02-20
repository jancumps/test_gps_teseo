#include <gtest/gtest.h>
import nmea;

class gllTest : public testing::Test {
protected:
    gllTest() : parse_ok(false) {}
    void SetUp() override {
        parse_ok = nmea::gll::from_data("$GPGLL,5051.83778,N,00422.55809,S,185427.150,A,N*4F", o);
    }
    nmea::gll o;
    bool parse_ok;
};

TEST_F(gllTest, parse) {
    EXPECT_TRUE(parse_ok) << "parse failed";
}

TEST_F(gllTest, valid) {
    EXPECT_TRUE(o.valid);
}

TEST_F(gllTest, source) {
    EXPECT_TRUE(o.source == nmea::talker_id::gps);
}

TEST_F(gllTest, lat) {
    EXPECT_FLOAT_EQ(o.lat, 50.8639641);
}

TEST_F(gllTest, lon) {
    EXPECT_FLOAT_EQ(o.lon, 4.37596798);
}

TEST_F(gllTest, time) {
    EXPECT_EQ((int)(o.t.hours().count()), 18) << "hours wrong. expected: 18. got: " << (int)(o.t.hours().count());
    EXPECT_EQ((int)(o.t.minutes().count()), 54) << "minutes wrong";
    EXPECT_EQ((int)(o.t.seconds().count()), 27) << "seconds wrong";
    EXPECT_EQ((int)(o.t.subseconds().count()), 150) << "subseconds wrong";
}