#ifndef STAFF_HPP
#define STAFF_HPP

#include "../magic.hpp"

class Staff: public Magic{
private:
    vector<int> lastTurnMove;
    int echoCooldown = 0;

public:
    Staff(string name);
    Staff(const Staff& other);
    
    string use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellIndex) override;
    
    void setEcho(vector<int> lastTurnMove);
    vector<int> getEcho();
    
    string stormChain(shared_ptr<Team> targetTeam, shared_ptr<Character> mainTarget);
    void mysticEcho();
    string staffOfEchoes(shared_ptr<Team> currentTeam, shared_ptr<Character> holder);
    string chaoticFlare(shared_ptr<Team> targetTeam, shared_ptr<Character> holder);
};

#endif
