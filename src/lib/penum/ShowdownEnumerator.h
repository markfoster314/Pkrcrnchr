#ifndef PENUM_SHOWDOWNENUMERATOR_H_
#define PENUM_SHOWDOWNENUMERATOR_H_

#include "CardDistribution.h"
#include <boost/shared_ptr.hpp>
#include "../peval/PokerHandEvaluator.h"
#include <vector>

namespace pkrcrnchr
{
class ShowdownEnumerator
{
public:
    ShowdownEnumerator();

    /**
     * enumerate a poker scenario, with board support
     */
    std::vector<EquityResult>
    calculateEquity(const std::vector<CardDistribution>& dists,
                    const CardSet& board,
                    boost::shared_ptr<PokerHandEvaluator> peval) const;
};
}  // namespace pkrcrnchr

#endif  // PENUM_SHOWDOWNENUMERATOR_H_
