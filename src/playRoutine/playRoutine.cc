#include <iostream>
#include <cstring>
#include <string>

#include "playRoutine.hh"

PlayRoutine::PlayRoutine(Chess& chess)
  : chess_(chess)
{}

void
PlayRoutine::showTitle() {
  std::cout << "CHESS GAME!" << std::endl;
}

void
PlayRoutine::run() {
  while(!chess_.end()) {
    chess_.print();
    playP1();
    if (chess_.end()) {
      end(1);
    }
    chess_.print();
    playP2();
  } 
  end(2);
}

void
PlayRoutine::end(int player) {
  std::cout << "Player " << player << " wins !" << std::endl;
}

struct move
PlayRoutine::askMove() {
  struct move move = getMove();
  while(!chess_.isDoable(move)) {
    std::cout << "Impossible move !" << std::endl;
    move = getMove();
  }
  return move;
}

void
PlayRoutine::playP1() { 
  chess_.apply(askMove());
}

void
PlayRoutine::playP2() {
  chess_.apply(askMove());
}

struct move
PlayRoutine::getMove() {  
  while (true) {
    std::string line = std::string();
    std::getline(std::cin, line);
    if (line.length() == 0) {
      std::cin.clear();
      continue;
    }
    int posX;
    int posY;
    int newPosX;
    int newPosY;
    try {
      std::string tok1 = std::strtok((char *) line.c_str(), " ");
      std::string tok2 = std::strtok(nullptr     , " ");
      std::string tok3 = std::strtok(nullptr     , " ");
      std::string tok4 = std::strtok(nullptr     , "\n");
    
      posX = std::stoi(tok1);
      posY = std::stoi(tok2);
      newPosX = std::stoi(tok3);
      newPosY = std::stoi(tok4);
    }
    catch(...) {
      continue;
    }
    struct move move;
    move.posX = posX;
    move.posY = posY;
    move.newPosX = newPosX;
    move.newPosY = newPosY;
    return move;
  }
}
