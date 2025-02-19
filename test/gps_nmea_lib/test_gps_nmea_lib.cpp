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