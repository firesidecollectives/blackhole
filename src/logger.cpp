#include "blackhole/logger.hpp"

#include "blackhole/scoped.hpp"

#include "blackhole/detail/unimplemented.hpp"

namespace blackhole {

logger_t::~logger_t() {}

auto
logger_t::scoped(attributes_t) -> scoped_t {
    BLACKHOLE_UNIMPLEMENTED();
    std::abort();
}

}  // namespace blackhole
