#include "../include/Board.h"

Board::Board(int sHeight, int sWidth, string textureFile){
  int i, j;

  //initialize the height, make the texture
  spaceHeight = sHeight;
  spaceWidth = sWidth;
  num_enemies = 0;
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
  protag = new Character(100, 0, 0, 6, 0.0, SDL_FLIP_NONE, 5, 40, 100, "./images/protagonist.png", &board);
}

void Board::make_board(string path){
  int i, j;
  int enem_x, enem_y;
  string row;
  string enemies_str;
  ifstream iFSS(path);

  //read in each line of text, represents
  while(iFSS >> row && strcmp(row.c_str(), "end_map") != 0){
    board.push_back(row);
  }

  //make rectangles for the board
  board_rects.resize(board.size() );
  for(i = 0; i < board.size(); i++){
    board_rects.at(i).resize(board.at(i).size(), NULL );

    for(j = 0; j < board.at(i).size(); j++){
      //'0' is a wall square, make non-walls NULL
      if(board.at(i).at(j) == '0'){
        board_rects.at(i).at(j) = new SDL_Rect();
        board_rects.at(i).at(j)->x = j * spaceWidth;
        board_rects.at(i).at(j)->y = i * spaceHeight;
        board_rects.at(i).at(j)->w = spaceWidth;
        board_rects.at(i).at(j)->h = spaceHeight;

        walls.push_back(board_rects.at(i).at(j) );

        printf("%d,%d ", board_rects.at(i).at(j)->x, board_rects.at(i).at(j)->y );
      }
    }
    printf("\n");
  }

  //push back a rectangle for the outside edge
  //my convention is that the last rectangle in the vector is the boundary
  walls.push_back(new SDL_Rect() );
  walls.at(walls.size()-1 )->x = 0;
  walls.at(walls.size()-1 )->y = 0;
  walls.at(walls.size()-1 )->w = 1280;
  walls.at(walls.size()-1 )->h = 720;

  //read in number of enemies
  iFSS >> enemies_str;
  sscanf(enemies_str.c_str(), "%d", &num_enemies);

  for(i = 0; i < num_enemies; i++){
    //this is to check make sure the enemey isnt spawned in a wall.
    //need to refine this b/c it doesn't check all corners.
    do{
      enem_x = rand() % 1280;
      enem_y = rand() % 720;
    } while(board.at(enem_y / spaceHeight).at(enem_x / spaceWidth) == '0');
    enemies.push_back( new Antagonist(100, enem_x, enem_y, 3, 0.0, SDL_FLIP_NONE, 5, 40, 40, "./images/blob.png", &board) );
  }

  //initialize the enemies' target
  for(i = 0; i < enemies.size(); i++){
    enemies.at(i)->set_target(protag);
    enemies.at(i)->initProjectile(10, protag);
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

void Board::move_entities(vector<SDL_Rect*>* walls){
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

//this is a way to generate nearby walls to check for collisions
vector<SDL_Rect*>* Board::gen_walls(Character* target){
  return &walls;
}
