#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

#define UNDEF -1
#define TRUE 1
#define FALSE 0

uint numVars;
uint numClauses;
vector<vector<int> > clauses;
vector<int> model;
vector<int> modelStack;
uint indexOfNextLitToPropagate;
uint decisionLevel;

//----------------------------------------------//
//---------- Propagation ----------------------//
vector<vector<int> > positiveOccurrences;
vector<vector<int> > negativeOccurrences;


//----------------------------------------------//
//---------- Heuristic  -----------------------//
vector<double> varScore;
int minScore = 0;
int maxScore = 0;
int flag = 0;
double payOff = 0.1;




//----------------------------------------------//
//---------- Output  -----------------------//
int backtracks;
int decisions;
int propagations;
void output(bool x){
  if (!x) cout << "UNSATISFIABLE ";
  else cout << "SATISFIABLE ";
  cout << decisions << " " << propagations << " " << backtracks << endl;
}
//-----------------------------------------------

void readClauses( ){
  // Skip comments
  char c = cin.get();
  while (c == 'c') {
    while (c != '\n') c = cin.get();
    c = cin.get();
  }
  // Read "cnf numVars numClauses"
  string aux;
  cin >> aux >> numVars >> numClauses;
  clauses.resize(numClauses);

  positiveOccurrences.resize(numVars+1);
  negativeOccurrences.resize(numVars+1);

  varScore.resize(numVars+1,0);
  flag = numVars;

  backtracks = decisions = propagations = 0;
  // Read clauses
  for (uint i = 0; i < numClauses; ++i) {
    int lit;
    while (cin >> lit and lit != 0){
      clauses[i].push_back(lit);
      lit > 0 ? positiveOccurrences[lit].push_back(i) : negativeOccurrences[-lit].push_back(i);
      ++varScore[abs(lit)];
    }
  }
}



int currentValueInModel(int lit){
  if (lit >= 0) return model[lit];
  else {
    if (model[-lit] == UNDEF) return UNDEF;
    else return 1 - model[-lit];
  }
}


void setLiteralToTrue(int lit){
  modelStack.push_back(lit);
  if (lit > 0) model[lit] = TRUE;
  else model[-lit] = FALSE;
}


bool propagateGivesConflict ( ) {
  while ( indexOfNextLitToPropagate < modelStack.size() ) {
    int lit = modelStack[indexOfNextLitToPropagate];
    ++indexOfNextLitToPropagate;
    vector<int>* whereToLook = lit > 0 ? &negativeOccurrences[lit] : &positiveOccurrences[-lit];
    for (uint i = 0; i < whereToLook->size(); ++i) {
      bool someLitTrue = false;
      int numUndefs = 0;
      int lastLitUndef = 0;
      for (uint k = 0; not someLitTrue and k < clauses[(*whereToLook)[i]].size(); ++k){
	      int val = currentValueInModel(clauses[(*whereToLook)[i]][k]);
	      if (val == TRUE) someLitTrue = true;
	      else if (val == UNDEF){ ++numUndefs; lastLitUndef = clauses[(*whereToLook)[i]][k]; }
      }
      if (not someLitTrue and numUndefs == 0) {
        ++backtracks;
        --flag;
        if (flag == 0) {
          flag = numVars;
          payOff+=0.1;
        }
        varScore[abs(lit)]+= payOff;

        return true; // conflict! all lits false
      }
      else if (not someLitTrue and numUndefs == 1) {
        ++propagations;
        setLiteralToTrue(lastLitUndef);
      }
    }
  }
  return false;
}


void backtrack(){
  uint i = modelStack.size() -1;
  int lit = 0;
  while (modelStack[i] != 0){ // 0 is the DL mark
    lit = modelStack[i];
    model[abs(lit)] = UNDEF;
    modelStack.pop_back();
    --i;
  }
  // at this point, lit is the last decision
  modelStack.pop_back(); // remove the DL mark
  --decisionLevel;
  indexOfNextLitToPropagate = modelStack.size();
  setLiteralToTrue(-lit);  // reverse last decision
}


// Heuristic for finding the next decision literal:
int getNextDecisionLiteral(){
  ++decisions;
  int max = -1;
  int lit = -1;

  for (int i = 1; i <= varScore.size(); ++i){
    if (model[i] == UNDEF and varScore[i] > max) {
      max = varScore[i];
      lit = i;
    }
  }
  if (lit > 0) return lit;
  return 0;

  //for (uint i = 1; i <= numVars; ++i) // stupid heuristic:
  //  if (model[i] == UNDEF) return i;  // returns first UNDEF var, positively
  //return 0; // reurns 0 when all literals are defined
}

void checkmodel(){
  for (int i = 0; i < numClauses; ++i){
    bool someTrue = false;
    for (int j = 0; not someTrue and j < clauses[i].size(); ++j)
      someTrue = (currentValueInModel(clauses[i][j]) == TRUE);
    if (not someTrue) {
      cout << "Error in model, clause is not satisfied:";
      for (int j = 0; j < clauses[i].size(); ++j) cout << clauses[i][j] << " ";
      cout << endl;
      exit(1);
    }
  }
}

int main(){
  srand (time(NULL));
  readClauses(); // reads numVars, numClauses and clauses
  model.resize(numVars+1,UNDEF);
  indexOfNextLitToPropagate = 0;
  decisionLevel = 0;

  // Take care of initial unit clauses, if any
  for (uint i = 0; i < numClauses; ++i)
    if (clauses[i].size() == 1) {
      int lit = clauses[i][0];
      int val = currentValueInModel(lit);
      if (val == FALSE) {output(false); return 10;}
      else if (val == UNDEF) setLiteralToTrue(lit);
    }

  // DPLL algorithm
  while (true) {
    while ( propagateGivesConflict() ) {
      if ( decisionLevel == 0) { output(false); return 10; }
      backtrack();
    }
    int decisionLit = getNextDecisionLiteral();
    if (decisionLit == 0) { checkmodel(); output(true); return 20; }
    // start new decision level:
    modelStack.push_back(0);  // push mark indicating new DL
    ++indexOfNextLitToPropagate;
    ++decisionLevel;
    setLiteralToTrue(decisionLit);    // now push decisionLit on top of the mark
  }
}
