#include "osl/state/numEffectState.h"
#include "osl/effect_util/effectUtil.h"
#include "osl/container/moveVector.h"
#include "osl/record/csa.h"
#include "osl/record/csaIOError.h"
#include "osl/move_generator/legalMoves.h"
#include <boost/random/mersenne_twister.hpp>
#include <string>
#include <sys/time.h>

namespace osl {
  void
  showState(const NumEffectState& state)
  {
    std::cout << state << std::endl;
  }

  Move
  selectMove(const NumEffectState& state, const MoveVector& moves)
  {
    static boost::mt11213b generator(random());
    return moves[generator() % moves.size()];
  }

  bool
  isMated(const NumEffectState& state)
  {
    return state.inCheck(alt(state.turn()));
  }

  bool
  computerOperate(NumEffectState& state)
  {
    MoveVector moves;
    LegalMoves::generate(state, moves);
    if (moves.empty()) {
      std::cerr << "You Win!\n";
      return true;
    }
    const Move my_move = selectMove(state, moves);
    assert(state.isValidMove(my_move));
    state.makeMove(my_move);

    showState(state);
    csaShow(std::cout, my_move);
    std::cout << "\n";

    if (isMated(state)) {
      std::cerr << "You Lose...";
      return true;
    }

    return false;
  }

  bool
  playerOperate(NumEffectState& state, std::string line)
  {
    Move op_move;
    try {
      op_move = record::csa::strToMove(line, state);
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << std::endl;
      return true;
    }

    if (! state.isValidMove(op_move)) {
      return true;
    }

    state.makeMove(op_move);

    showState(state);
    csaShow(std::cout, op_move);
    std::cout << "\n";

    return false;
  }

  std::string
  inputLine(void)
  {
    std::string line;
    if (! std::getline(std::cin, line)) {
      return NULL;
    }
    return line;
  }
}

int
main()
{
  using namespace osl;

  srandom(time(0));

  NumEffectState state((SimpleState(HIRATE)));
  while (true) {
    bool ended = computerOperate(state);
    if (ended) {
      break;
    }

    std::string line = inputLine();
    bool failed = playerOperate(state, line);
    if (failed) {
      break;
    }
  }
}
