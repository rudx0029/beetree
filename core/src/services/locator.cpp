#include "beetree/services/locator.hpp"
#include "beetree/core/tokens.hpp"

namespace bte {
void internal::assert_valid_svc(const void* svc) { assert_valid(svc, tokens::FatalNotFound); }
}  // namespace bte