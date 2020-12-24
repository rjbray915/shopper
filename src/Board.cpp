#include "../include/Board.h"

Board::Board(int sHeight, int sWidth, string textureFile){
  int i, j;

  //initialize the height, make the texture
  spaceHeight = sHeight;
  spaceWidth = sWidth;
  texture_plate = new LTexture();
  texture_plate->loadFromFile(textureFile);

  //find how many squares there are
  int numX, numY;
  numX = texture_plate->getWidth() / spaceWidth;
  numY = texture_plate->getHeight() / spaceHeight;

  //create the squares for each texture
  for(j = 0; j < numY; j++ ){
    for(i = 0; i < numX; i++){
      squares.push_back( {spaceWidth * i, spaceHeight * j, spaceWidth, spaceHeight} );
    }
  }

  //make vector of enemies. index 0 is ALWAYS the main char
  protag = new Character(100, 500, 500, 6, 0.0, SDL_FLIP_NONE, 5, 40, 100, "./images/protagonist.png");
  enemies.push_back( new Antagonist(100, 0, 0, 3, 0.0, SDL_FLIP_NONE, 1, 60, 100, "./images/antiTest.png") );

  //initialize the enemies' target
  for(i = 0; i < enemies.size(); i++){
    enemies.at(i)->set_target(protag );
    enemies.at(i)->initProjectile(10, protag);
  }
}

void Board::make_board(string path){
  string row;
  ifstream iFSS(path);

  //read in each line of text, represents
  while(iFSS >> row){
    board.push_back(row);
  }
}

void Board::render_board(){
  int i, j;

  //each letter in the board represents a texture. all are numbers, so offset by '0'
  for(i = 0; i < board.size(); i++){
    for(j = 0; j < board.at(i).size(); j++){
      texture_plate->render(j * spaceWidth, i * spaceHeight, &squares.at(board.at(i).at(j) - '0'), 0.0, NULL, SDL_FLIP_NONE);
    }
  }
}

void Board::move_entities(vector<SDL_Rect*> walls){
  int i;

  protag->move(walls);

  for(i = 0; i < enemies.size(); i++){
    enemies.at(i)->move(walls);
  }
}

void Board::render_entities(){
  int i;

  protag->render();

  for(i = 0; i < enemies.size(); i++){
    enemies.at(i)->render();
  }
}

void Board::dan_handle(SDL_Event* e){
  protag->handleEvent(e);
}
