//
//  project2.h
//  project2
//
//  Created by Kate Findlay on 10/6/14.
//  Copyright (c) 2014 Kate Findlay. All rights reserved.
//

#ifndef __project2__project2__
#define __project2__project2__

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include <cstring>
#include <stdio.h>
#include <iomanip>

#include "P2random.h"
#include "eecs281_priority_queue.h"
#include "poorman_priority_queue.h"
//#include "pairing_priority_queue.h"
#include "sorted_priority_queue.h"
#include "heap_priority_queue.h"

using namespace std;

struct Tile {
    int row;
    int col;
    int rubbleVal;
    bool cleared;
    bool visited;
};

struct MineInfo {
    Tile *start;
    int size;
    char inputMode;
    char * mineFile;
    int tilesCleared;
    long int rubbleCleared;
    bool end;
    int stats;
};

struct clearingTile {
    bool operator() (const Tile *t1, const Tile *t2) const {
        if(t1->cleared && t2->cleared) {
            if(t1->col == t2->col) {
                return t1->row > t2->row;
            } else {
                return t1->col > t2->col;
            }
        } else if(!t1->cleared && !t2->cleared) {
            if(t1->rubbleVal == t2->rubbleVal) {
                if(t1->col == t2->col) {
                    return t1->row > t2->row;
                } else {
                    return t1->col > t2->col;
                }
            } else {
                return t1->rubbleVal > t2->rubbleVal;
            }
        } else {
            if(t2->cleared) {
                return t1->rubbleVal != -1;
            } else {
                return t2->rubbleVal == -1;
            }
        }
    }
};

struct easiestTile {
    bool operator() (const Tile *t1, const Tile *t2) const {
        if(t1->rubbleVal == t2->rubbleVal) {
            if(t1->col == t2->col) {
                return t1->row > t2->row;
            } else {
                return t1->col > t2->col;
            }
        } else {
            return t1->rubbleVal > t2->rubbleVal;
        }
    }
};

struct hardestTile {
    bool operator() (const Tile *t1, const Tile *t2) const {
        if(t1->rubbleVal == t2->rubbleVal) {
            if(t1->col == t2->col) {
                return t1->row < t2->row;
            } else {
                return t1->col < t2->col;
            }
        } else {
            return t1->rubbleVal < t2->rubbleVal;
        }
    }
};

typedef vector<vector<Tile>> Mine;
vector<Tile*> clearedTiles = vector<Tile*>();

eecs281_priority_queue<Tile*, clearingTile> * pqueue;
eecs281_priority_queue<Tile*, clearingTile> * tntQueue;


poorman_priority_queue<Tile*, clearingTile> poorman;
sorted_priority_queue<Tile*, clearingTile> sorted;
heap_priority_queue<Tile*, clearingTile> binary;
//pairing_priority_queue<Tile*, easiestTile> pairing;

poorman_priority_queue<Tile*, clearingTile> poormanTNT;
sorted_priority_queue<Tile*, clearingTile> sortedTNT;
heap_priority_queue<Tile*, clearingTile> binaryTNT;
//pairing_priority_queue<Tile*, easiestTile> pairingTNT;

eecs281_priority_queue<Tile*, easiestTile> * easyOutput;
eecs281_priority_queue<Tile*, hardestTile> * hardOutput;
heap_priority_queue<Tile*, easiestTile> easyBinary;
heap_priority_queue<Tile*, hardestTile> hardBinary;


void fillMine(Mine &mine, MineInfo &mineInfo);
void initializeMine(Mine &mine, MineInfo &mineInfo);
void findPath(Mine &mine, MineInfo &mineInfo);
void getOpts(int argc, char *argv[], MineInfo &mineInfo);
void printMine(Mine &mine, MineInfo mineInfo);
void output(MineInfo &mineInfo);

void clearCurTile(Tile *cur, Mine &mine, MineInfo &mineInfo);
void addToPath(Tile *cur, Mine &mine, MineInfo &mineInfo);
void addToTNT(Tile *cur, Mine &mine, MineInfo &mineInfo);

bool checkNorth(Tile *cur) { return (cur->row-1 >= 0); }
Tile* getNorth(Tile *cur, Mine &mine) { return &mine[cur->row-1][cur->col]; }
bool checkEast(Tile *cur, int size) { return (cur->col+1 < size); }
Tile* getEast(Tile *cur, Mine &mine) { return &mine[cur->row][cur->col+1]; }
bool checkSouth(Tile *cur, int size) { return (cur->row+1 < size); }
Tile* getSouth(Tile *cur, Mine &mine) { return &mine[cur->row+1][cur->col]; }
bool checkWest(Tile *cur) { return (cur->col-1 >= 0); }
Tile* getWest(Tile *cur, Mine &mine) { return &mine[cur->row][cur->col-1]; }
bool isEdge(Tile *cur, int size) {
    return (!(checkNorth(cur) && checkEast(cur, size) && checkSouth(cur, size) && checkWest(cur)));
}


void statsOutput(MineInfo &mineInfo);

#endif /* defined(__project2__project2__) */
