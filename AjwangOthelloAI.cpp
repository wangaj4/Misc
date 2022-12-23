// AjwangOthelloAI.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include "AjwangOthelloAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, wangaj4::MyOthelloAI, "Ajwang's Othello AI (Required)");


std::pair<int, int> wangaj4::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    // implementation of the AI goes here
    std::pair<int,int> answer;



    bool black = state.isBlackTurn();

    //When we're passed the state, the next to move is us, so this bool 
        //determines whether we're playing for black or white



    //Iterate through all cells in the board, if state.isValidMove(), make a copy of 
        //the board, make that move, call search on it to determine eval value
        //If it's higher than maxEval, set bestX and bestY to it and set maxEval
    int bestX = 4;
    int bestY = 5;
    int maxEval = -999999;
    int depth = 4;

    for(int x = 0;x < state.board().width();x++){
        for(int y = 0;y < state.board().height();y++){
            
            if(state.isValidMove(x,y)){
                
                std::unique_ptr copy = state.clone();
                copy->makeMove(x,y);
                OthelloGameState* potentialMoveState = copy.get();

                int value = search(*potentialMoveState, depth, black);
                if(value>maxEval){
                    maxEval=value;
                    bestX=x;
                    bestY=y;
                }
               

            }
        }
    }

    answer.first=bestX;
    answer.second=bestY;
    return answer;
}

int wangaj4::MyOthelloAI::search(const OthelloGameState& state, int depth, bool black){
    //bool black determines whether we're trying to evaluate the best move for black
        //if it's false, we're trying to evaluate the best move for white instead
    if(depth==0){
        return eval(state,black);
    }

    


    if((black && state.isBlackTurn()) || (!black && state.isWhiteTurn())){
        //yup, it's my turn, find best move, maximum value

        int maxEval = -99999;
        //Iterate through all possible moves, keep track of the one where we're maximum eval
        
        for(int x = 0;x < state.board().width();x++){
            for(int y = 0;y < state.board().height();y++){
                if(state.isValidMove(x,y)){

                    std::unique_ptr copy = state.clone();
                    copy->makeMove(x,y);
                    OthelloGameState* possibleMove = copy.get();

                    int value = search(*possibleMove, depth-1, black);
                    if(value>maxEval){
                        maxEval=value;
                  
                    }

                }
            }
        }
        return maxEval;

    }

/////////////////////////////////////////////////////////////////////////////////////////////////

    else{
        //nope, not my turn, find the minimum value
     
        int minEval = 99999;
        //Iterate through all possible moves, keep track of the one where we're maximum eval
        
        for(int x = 0;x < state.board().width();x++){
            for(int y = 0;y < state.board().height();y++){
                if(state.isValidMove(x,y)){

                    std::unique_ptr copy = state.clone();
                    copy->makeMove(x,y);
                    OthelloGameState* possibleMove = copy.get();

                    int value = search(*possibleMove, depth-1, black);
                    if(value<minEval){
                        minEval=value;
                   
                    }

                }
            }
        }
        return minEval;
    }





}

int wangaj4::MyOthelloAI::eval(const OthelloGameState& state, bool black){
    //returns number of my cells - opponent's cells
    int numBlack = state.blackScore();
    int numWhite = state.whiteScore();
    if(black){
        return numBlack - numWhite;
    }else{
        return numWhite - numBlack;
    }
}