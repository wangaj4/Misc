// AjwangOthelloAI.hpp

#include "OthelloAI.hpp"


namespace wangaj4
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
        int search(const OthelloGameState& state, int depth, bool black);
        int eval(const OthelloGameState& state, bool black);
    };
}
