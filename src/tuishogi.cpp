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
      std::cout << "You Win!" << std::endl;
      return true;
    }
    const Move my_move = selectMove(state, moves);
    assert(state.isValidMove(my_move));
    state.makeMove(my_move);

    showState(state);
    csaShow(std::cout, my_move);
    std::cout << "\n";

    if (isMated(state)) {
      std::cout << "You Lose..." << std::endl;
      return true;
    }

    return false;
  }

  bool
  playerOperate(NumEffectState& state, std::string line)
  {
    Move op_move;
    if (line.length() == 4) {
      MoveVector moves;
      LegalMoves::generate(state, moves);
      int i;
      for (i = 0; i < moves.size(); i++) {
        Move m = moves[i];
        Square from = m.from();
        Square to = m.to();
        if (((int)line[0] - (int)'0') == from.x() &&
            ((int)line[1] - (int)'0') == from.y() &&
            ((int)line[2] - (int)'0') == to.x() &&
            ((int)line[3] - (int)'0') == to.y()) {
          op_move = m;
          break;
        }
      }
    } else if (line.length() != 7) {
      std::cout << "error: invalid format." << std::endl;
      return true;
    } else {
      try {
        op_move = record::csa::strToMove(line, state);
      } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return true;
      }
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
