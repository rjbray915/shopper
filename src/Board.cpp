#include "../include/Board.h"
Board::Board(int sHeight, int sWidth, string textureFile){
  int i, j;

  spaceHeight = sHeight;
  spaceWidth = sWidth;
  texture_plate = new LTexture();
  texture_plate->loadFromFile(textureFile);

  //find how many squares there are
  int numX, numY;
  numX = texture_plate->getWidth() / spaceWidth;
  numY = texture_plate->getHeight() / spaceHeight;

  for(j = 0; j < numY; j++ ){
    for(i = 0; i < numX; i++){
      squares.push_back( {spaceWidth * i, spaceHeight * j, spaceWidth, spaceHeight} );
    }
  }
}

void Board::make_board(string path){
  string row;
  ifstream iFSS(path);

  while(iFSS >> row){
    board.push_back(row);
  }
}

void Board::render_board(){
  int i, j;

  for(i = 0; i < board.size(); i++){
    for(j = 0; j < board.at(i).size(); j++){
      texture_plate->render(j * spaceWidth, i * spaceHeight, &squares.at(board.at(i).at(j) - '0'), 0.0, NULL, SDL_FLIP_NONE);
    }
  }
}
