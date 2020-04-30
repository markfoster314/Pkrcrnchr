#include <boost/program_options.hpp>
#include <iostream>
#include "../../lib/pkrcrnchr/penum/ShowdownEnumerator.h"
#include <vector>

using namespace pkrcrnchr;
namespace po = boost::program_options;
using namespace std;

/**
 * Sample acceptable input:
 * $ g++ main.cpp -o main
 * $ ./main AsAd 4sKd 4c8c2c 
 */
int main(int argc, char** argv)
{
    // First arg is user hand, second arg is opponent hand, third arg is board, h stands for hold em
    string game = "h";
    vector<string> hands{argv[1], argv[2]};
    string board = argv[3]; 

    // allocate evaluator and create card distributions
    boost::shared_ptr<PokerHandEvaluator> evaluator =
        PokerHandEvaluator::alloc(game);
    vector<CardDistribution> handDists;
    for (const string& hand : hands)
    {
        handDists.emplace_back();
        handDists.back().parse(hand);
    }

    // fill with random if necessary
    if (handDists.size() == 1)
    {
        handDists.emplace_back();
        handDists.back().fill(evaluator->handSize());
    }


    // calcuate the results and print them
    ShowdownEnumerator showdown;
    vector<EquityResult> results =
        showdown.calculateEquity(handDists, CardSet(board), evaluator);

    double total = 0.0;
    for (const EquityResult& result : results)
    {
        total += result.winShares + result.tieShares;
    }


    for (size_t i = 0; i < results.size(); ++i)
    {
        double equity =
            (results[i].winShares + results[i].tieShares) / total;
        string handDesc =
            (i < hands.size()) ? "The hand " + hands[i] : "A random hand";
        cout << handDesc << " has " << equity * 100. << " % equity ("
                << results[i].str() << ")" << endl;
    }


    cout << "You have entered " << argc 
         << " arguments:" << "\n"; 
  

    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 
  
    return 0; 

}
