#include "Mocks.hpp"

using namespace blackhole;

TEST(string_t, FormatSingleAttribute) {
    log::record_t record;
    record.attributes = {
        keyword::message() = "le message"
    };
    std::string pattern("[%(message)s]");
    formatter::string_t fmt(pattern);
    EXPECT_EQ("[le message]", fmt.format(record));
}

TEST(string_t, FormatMultipleAttributes) {
    log::record_t record;
    record.attributes = {
        keyword::message() = "le message",
        { "timestamp", { "le timestamp" } }
    };
    std::string pattern("[%(timestamp)s]: %(message)s");
    formatter::string_t fmt(pattern);
    EXPECT_EQ("[le timestamp]: le message", fmt.format(record));
}

TEST(string_t, FormatMultipleAttributesMoreThanExists) {
    log::record_t record;
    record.attributes = {
        keyword::message() = "le message",
        { "timestamp", { "le timestamp" } },
        { "source", { "le source" } }
    };
    std::string pattern("[%(timestamp)s]: %(message)s");
    formatter::string_t fmt(pattern);
    EXPECT_EQ("[le timestamp]: le message", fmt.format(record));
}

TEST(string_t, ThrowsExceptionWhenAttributeNameNotProvided) {
    log::record_t record;
    record.attributes = {
        keyword::message() = "le message"
    };
    std::string pattern("[%(timestamp)s]: %(message)s");
    formatter::string_t fmt(pattern);
    EXPECT_THROW(fmt.format(record), error_t);
}

TEST(string_t, FormatOtherLocalAttribute) {
    log::record_t record;
    record.attributes = {
        { "uuid", { "123-456" } },
    };
    std::string pattern("[%(...L)s]");
    formatter::string_t formatter(pattern);
    EXPECT_EQ("['uuid': '123-456']", formatter.format(record));
}

TEST(string_t, FormatOtherLocalAttributes) {
    log::record_t record;
    record.attributes = {
        { "uuid", { "123-456" } },
        { "answer to life the universe and everything", { 42 } }
    };
    std::string pattern("[%(...L)s]");
    formatter::string_t formatter(pattern);
    std::string actual = formatter.format(record);
    EXPECT_TRUE(actual.find("'answer to life the universe and everything': '42'") != std::string::npos);
    EXPECT_TRUE(actual.find("'uuid': '123-456'") != std::string::npos);
}

TEST(string_t, ComplexFormatWithOtherLocalAttributes) {
    log::record_t record;
    record.attributes = {
        { "timestamp", { "1960-01-01 00:00:00", log::attribute_t::type_t::event } },
        { "level", { "INFO", log::attribute_t::type_t::event } },
        keyword::message() = "le message",
        { "uuid", { "123-456" } },
        { "answer to life the universe and everything", { 42 } }
    };
    std::string pattern("[%(timestamp)s] [%(level)s]: %(message)s [%(...L)s]");
    formatter::string_t formatter(pattern);
    std::string actual = formatter.format(record);
    EXPECT_TRUE(boost::starts_with(actual, "[1960-01-01 00:00:00] [INFO]: le message ["));
    EXPECT_TRUE(actual.find("'answer to life the universe and everything': '42'") != std::string::npos);
    EXPECT_TRUE(actual.find("'uuid': '123-456'") != std::string::npos);
}

//!@todo:
//! implement %(...A)s handling in formatter::string
//! [L|E|G|T|U].
