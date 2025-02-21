#include <gtest/gtest.h>
#include <string>
import nmea;

class gllTest : public ::testing::TestWithParam<std::tuple<std::string, bool>>  {
protected:
    gllTest() : parse_ok(false) {}
    nmea::gll o;
};

TEST_P(gllTest, parsetest) {
    bool expected = std::get<1>(GetParam());
    std::string s = std::get<0>(GetParam());
    ASSERT_EQ(expected, nmea::gll::from_data(s, o));
}

INSTANTIATE_TEST_CASE_P(
    parsetest,
    gllTest,
    ::testing::Values(
            std::make_tuple("$GPGLL,5051.83778,N,00422.55809,S,185427.150,A,N*4F", true),
            std::make_tuple("$GPGLL,5051.83778,N,00422.55809,S,185427.150,V,N*4F", true)));


/* TEST_F(gllTest, parse) {
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
} */