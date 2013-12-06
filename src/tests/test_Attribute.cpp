#include "Mocks.hpp"

TEST(Attribute, CanMakeCustomAttribute) {
    auto attribute = attr::make<std::int32_t>("custom", 42);
    EXPECT_EQ("custom", attribute.first);
    EXPECT_EQ(42, boost::get<std::int32_t>(attribute.second.value));
}

TEST(Attribute, TimestampIsEventAttribute) {
    log::attribute_pair_t pair = (keyword::timestamp_id() = std::time_t(0));
    EXPECT_EQ(log::attribute_t::type_t::event, pair.second.type);
}

TEST(Attribute, SeverityIsEventAttribute) {
    enum class level { debug };
    log::attribute_pair_t pair = (keyword::severity<level>() = level::debug);
    EXPECT_EQ(log::attribute_t::type_t::event, pair.second.type);
}

TEST(Attribute, MessageIsEventAttribute) {
    log::attribute_pair_t pair = (keyword::message() = "le message");
    EXPECT_EQ(log::attribute_t::type_t::event, pair.second.type);
}
