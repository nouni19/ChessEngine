#include <iostream>
#include "chess.cpp"
#include "time.h"
typedef long long int ll;
using namespace std;
using namespace chess;

ll MAX_DEPTH = 4;

double evaluate(Board board){
    if (board.is_stalemate())
        return 0;
    Outcome outcome = *board.outcome();
    if(outcome.winner == true)
        return 200;
    if(outcome.winner == false)
        return -200;
    double res = 0;
    for(auto &c : board.fen()){
        if(c == ' '){
            break;
        }
        switch (c){
            case 'p':
                res++;
                break;
            case 'P':
                res--;
                break;
            case 'b':
                res += 3;
                break;
            case 'B':
                res -= 3;
                break;
            case 'n':
                res += 3;
                break;
            case 'N':
                res -= 3;
                break;
            case 'r':
                res += 5;
                break;
            case 'R':
                res -= 5;
                break;
            case 'q':
                res += 9;
                break;
            case 'Q':
                res -= 9;
                break;
        }
    }
    res = -res;
    if(board.turn == WHITE){
        res += 0.05*board.legal_moves().count();
        board.turn = BLACK;
        res -= 0.05*board.legal_moves().count();
        board.turn = WHITE;
    } else if(board.turn == BLACK){
        res -= 0.05*board.legal_moves().count();
        board.turn = WHITE;
        res += 0.05*board.legal_moves().count();
        board.turn = BLACK;
    }
    return res;
}

typedef struct { 
    Move m;
    double d;
} BestMove;


BestMove minimax(Board pos, bool player, double alpha, double beta, ll depth){
    if (depth == 0){
        BestMove temp;
        temp.d = evaluate(pos);
        return temp;
    }
    Move best_move;
    if(player){
        for(auto &move : pos.legal_moves()){
            pos.push(move);
            double score = minimax(pos,false,alpha,beta,depth-1).d;
            pos.pop();
            if(score >= beta){
                BestMove temp;
                temp.d = beta;
                return temp;
            }
            if(score > alpha){
                best_move = move;
                alpha = score;
            }
        }
        if (depth == MAX_DEPTH){
            BestMove temp;
            temp.m = best_move;
            temp.d = alpha;
            return temp;
        }
        BestMove temp;
        temp.d = alpha;
        return temp;
    } else{
        for(auto &move : pos.legal_moves()){
            pos.push(move);
            double score = minimax(pos,true,alpha,beta,depth-1).d;
            pos.pop();
            if(score <= alpha){
                BestMove temp;
                temp.d = alpha;
                return temp;
            }
            if(score < beta){
                best_move = move;
                beta = score;
            }
        }
        if (depth == MAX_DEPTH){
            BestMove temp;
            temp.m = best_move;
            temp.d = beta;
            return temp;
        }
        BestMove temp;
        temp.d = beta;
        return temp;    
    }
}

BestMove nextmove(Board board){
    if (board.turn == WHITE){
        return minimax(board,true,-1000000000,1000000000,MAX_DEPTH);
    }
    return minimax(board,false,-1000000000,1000000000,MAX_DEPTH);
}

int main(){
    Board board;
    string s;
    cout << "Depth: ";
    cin >> MAX_DEPTH;
    cout << "\nYou are: ";
    cin >> s;
    cout << "\n";
    if (s == "white"){
        cout << "Your move: ";
        bool worked = false;
        while (!worked){
            try{
                string temp;
                cin >> temp;
                board.push_san(temp);
                cout << '\n';
                worked = true;
            } catch (string nothing){
                cout << "Invalid!\n";
            }
        }
    }
    for(;;){
        time_t start,end;
        time(&start);
        BestMove next_move = nextmove(board);
        time(&end);
        cout << board.san(next_move.m) << " - score: " << next_move.d << " - time taken: " << double(end-start) << "s\n";
        board.push(next_move.m);
        cout << "Your move: ";
        string temp;
        cin >> temp;
        board.push_san(temp);
        cout << '\n';
    }
    return 0;
}