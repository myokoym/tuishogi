#include <cppcutter.h>
#include "tuishogi.cpp"

namespace tuishogi {

  using namespace osl;

  void
  test_showState(void)
  {
    // Arrange
    std::stringbuf  string_out;
    std::streambuf* std_out = std::cout.rdbuf(&string_out);
    NumEffectState state((SimpleState(HIRATE)));
    const char* expected = "\
P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n\
P2 * -HI *  *  *  *  * -KA * \n\
P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n\
P4 *  *  *  *  *  *  *  *  * \n\
P5 *  *  *  *  *  *  *  *  * \n\
P6 *  *  *  *  *  *  *  *  * \n\
P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n\
P8 * +KA *  *  *  *  * +HI * \n\
P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n\
+\n\
\n";

    // Act
    showState(state);

    std::cout << std::flush;
    std::cout.rdbuf(std_out);

    // TODO assert it as a std::string
    std::string str = string_out.str();
    const char* actual = str.c_str();

    // Assert
    cut_assert_equal_string(expected, actual);
  }

  void
  test_isMated(void)
  {
    NumEffectState state((SimpleState(HIRATE)));
    bool mated = isMated(state);
    cut_assert_false(mated);
  }

  void
  test_computerOperate(void)
  {
    // TODO cleanup
    std::stringbuf  string_out;
    std::streambuf* std_out = std::cout.rdbuf(&string_out);
    NumEffectState state((SimpleState(HIRATE)));
    bool ended = computerOperate(state);
    std::cout << std::flush;
    std::cout.rdbuf(std_out);
    cut_assert_false(ended);
  }

  void
  test_playerOperate_valid(void)
  {
    // Arrange
    std::stringbuf  string_out;
    std::streambuf* std_out = std::cout.rdbuf(&string_out);
    NumEffectState state((SimpleState(HIRATE)));
    const char* expected = "\
P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n\
P2 * -HI *  *  *  *  * -KA * \n\
P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n\
P4 *  *  *  *  *  *  *  *  * \n\
P5 *  *  *  *  *  *  *  *  * \n\
P6 *  * +FU *  *  *  *  *  * \n\
P7+FU+FU * +FU+FU+FU+FU+FU+FU\n\
P8 * +KA *  *  *  *  * +HI * \n\
P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n\
-\n\
\n\
+7776FU\n";

    // Act
    bool failed = playerOperate(state, "+7776FU");

    std::cout << std::flush;
    std::cout.rdbuf(std_out);

    // TODO assert it as a std::string
    std::string str = string_out.str();
    const char* actual = str.c_str();

    // Assert
    cut_assert_false(failed);
    cut_assert_equal_string(expected, actual);
  }

  void
  test_playerOperate_invalid_movement(void)
  {
    // TODO cleanup
    std::stringbuf  string_out;
    std::streambuf* std_out = std::cout.rdbuf(&string_out);
    NumEffectState state((SimpleState(HIRATE)));
    bool failed = playerOperate(state, "+5251FU");
    std::cout << std::flush;
    std::cout.rdbuf(std_out);
    cut_assert_true(failed);
  }

  void
  test_playerOperate_invalid_format(void)
  {
    // TODO cleanup
    std::stringbuf  string_out;
    std::streambuf* std_out = std::cout.rdbuf(&string_out);
    NumEffectState state((SimpleState(HIRATE)));
    bool failed = playerOperate(state, "");
    std::cout << std::flush;
    std::cout.rdbuf(std_out);
    cut_assert_true(failed);
  }

}  // namespace tuishogi
