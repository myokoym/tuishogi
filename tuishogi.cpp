#include "osl/state/numEffectState.h"
#include "osl/effect_util/effectUtil.h"
#include "osl/container/moveVector.h"
#include "osl/record/csa.h"
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
}

int
main()
{
  using namespace osl;

  srandom(time(0));

  NumEffectState state((SimpleState(HIRATE)));
  std::string line;
  while (true)
  {
    // 自分の手を指す
    MoveVector moves;
    LegalMoves::generate(state, moves);
    if (moves.empty())
    {
      std::cerr << "make masita\n";
      break;
    }
    const Move my_move = selectMove(state, moves);
    assert(state.isValidMove(my_move));
    state.makeMove(my_move);

    showState(state);
    csaShow(std::cout, my_move);
    std::cout << "\n";

    if (isMated(state))
    {
      std::cerr << "checkmate!";
      break;
    }

    // 相手の指手を読みこむ
    if (! std::getline(std::cin, line))
      break;

    const Move op_move=record::csa::strToMove(line, state);
    if (! state.isValidMove(op_move))
      break;

    state.makeMove(op_move);

    showState(state);
    csaShow(std::cout, op_move);
    std::cout << "\n";
  }
}
