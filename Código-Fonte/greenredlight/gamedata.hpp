#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Right, Left, Up, Down};
enum class State { Start, Playing, GameOver, Win};

struct GameData {
  State m_state{State::Start};
    std::bitset<4> m_input;  // [left, right, up, down]
};
#endif