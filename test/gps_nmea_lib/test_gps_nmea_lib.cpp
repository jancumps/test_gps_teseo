#include <gtest/gtest.h>
#include <string>
import nmea;

// ==================================================================================
// template for parameterised parser tests
// generic fixture that allows to test any nmea parser class' parser function
template <class T>
class nmeaParsersTest : public ::testing::TestWithParam<std::tuple<std::string, bool>> {
protected:
    nmeaParsersTest() {}
    T o;
};

class gllParserTest : public nmeaParsersTest<nmea::gll> {};

TEST_P(gllParserTest, gllparsetest) {
    bool expected = std::get<1>(GetParam());
    std::string s = std::get<0>(GetParam());
    ASSERT_EQ(expected, o.from_data(s, o));
}

INSTANTIATE_TEST_CASE_P(
    parsetest,
    gllParserTest,
    ::testing::Values(
        std::make_tuple("$XXXXXXXX", false), // invalid payload
        std::make_tuple("", false), // empty payload
        std::make_tuple("$GPGLL,5051.83778,N,00422.55809,S,185427.150,A,N*4F", true),
        std::make_tuple("$GPGLL,5051.83778,N,00422.55809,S,185427.150,V,N*4F", true))
);

class ggaParserTest : public nmeaParsersTest<nmea::gga> {};


TEST_P(ggaParserTest, ggaparsetest) {
    bool expected = std::get<1>(GetParam());
    std::string s = std::get<0>(GetParam());
    ASSERT_EQ(expected, o.from_data(s, o));
}

INSTANTIATE_TEST_CASE_P(
    parsetest,
    ggaParserTest,
    ::testing::Values(
        std::make_tuple("$XXXXXXXX", false), // invalid payload
        std::make_tuple("", false), // empty payload
        std::make_tuple("$GPGGA,191237.000,5051.78066,N,00422.57079,E,1,05,3.7,027.26,M,47.3,M,,*65", true))
);

class gsaParserTest : public nmeaParsersTest<nmea::gsa> {};

TEST_P(gsaParserTest, gsaparsetest) {
    bool expected = std::get<1>(GetParam());
    std::string s = std::get<0>(GetParam());
    ASSERT_EQ(expected, o.from_data(s, o));
}

INSTANTIATE_TEST_CASE_P(
    parsetest,
    gsaParserTest,
    ::testing::Values(
        std::make_tuple("$XXXXXXXX", false), // invalid payload
        std::make_tuple("", false), // empty payload
        std::make_tuple("$GNGSA,A,3,15,18,,,,,,,,,,,4.7,3.7,2.9*2D", true),
        std::make_tuple("$GNGSA,A,3,73,65,81,,,,,,,,,,4.7,3.7,2.9*2E", true))
);


// ==================================================================================
// template for unit tests
template <class T>
class nmeaTest : public testing::Test {
protected:
    nmeaTest() {}
    T o;
};

// unit test for gll parser
class gllTest : public nmeaTest<nmea::gll> {
protected:
    gllTest() : parse_ok(false) {}
    void SetUp() override {
        parse_ok = o.from_data("$GPGLL,5051.83778,N,00422.55809,S,185427.150,A,N*4F", o);
    }
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

// unit test for gga parser
class ggaTest : public nmeaTest<nmea::gga> {
protected:
    ggaTest() : parse_ok(false) {}
    void SetUp() override {
        parse_ok = o.from_data("$GPGGA,191237.000,5051.78066,N,00422.57079,E,1,05,3.7,027.26,M,47.3,M,,*65", o);
    }
    bool parse_ok;
};
    
TEST_F(ggaTest, parse) {
    EXPECT_TRUE(parse_ok) << "parse failed";
}

TEST_F(ggaTest, source) {
    EXPECT_TRUE(o.source == nmea::talker_id::gps);
}
    
TEST_F(ggaTest, lat) {
    EXPECT_FLOAT_EQ(o.lat, 50.86301);
}
    
TEST_F(ggaTest, lon) {
    EXPECT_FLOAT_EQ(o.lon, 4.3761797);
}
 
TEST_F(ggaTest, time) {
    EXPECT_EQ((int)(o.t.hours().count()), 19) << "hours wrong. expected: 18. got: " << (int)(o.t.hours().count());
    EXPECT_EQ((int)(o.t.minutes().count()), 12) << "minutes wrong";
    EXPECT_EQ((int)(o.t.seconds().count()), 37) << "seconds wrong";
    EXPECT_EQ((int)(o.t.subseconds().count()), 0) << "subseconds wrong";
}