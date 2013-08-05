#include <cppcutter.h>
#include "tuishogi.cpp"

namespace tuishogi {

void
test_isMated(void)
{
  using namespace osl;
  NumEffectState state((SimpleState(HIRATE)));
  bool mated = isMated(state);
  cut_assert_false(mated);
}

}  // namespace tuishogi
