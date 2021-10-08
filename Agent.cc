// Agent.cc
//


#include <iostream>
#include <list>
#include "Agent.h"


using namespace std;

int MySearchEngine::HeuristicFunction(SearchState* state, SearchState* goalState) {
    return abs(state->location.X-goalState->location.X)+abs(state->location.Y-goalState->location.Y);
}

//	return 0;  not a good heuristic

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{

    currentLocation = Location(1,1);
    agentOrientation = RIGHT;
    lastAction = CLIMB;
    goldLocation = Location(0,0);

	agentHasGold = false;
    agentHasArrow = true;
	actionList.clear();
}

Orientation Agent::Change_face_to(Action action,Orientation agentOrientation){
    if(action==TURNLEFT){
        if(agentOrientation==RIGHT){agentOrientation=UP;}
        else if(agentOrientation==LEFT){agentOrientation=DOWN;}
        else if(agentOrientation==UP){agentOrientation=LEFT;}
        else{agentOrientation=RIGHT;}
    }
    else if(action==TURNRIGHT){
        if(agentOrientation==RIGHT){agentOrientation=DOWN;}
        else if(agentOrientation==LEFT){agentOrientation=UP;}
        else if(agentOrientation==UP){agentOrientation=RIGHT;}
        else{agentOrientation=LEFT;}
    }

    return agentOrientation;
}

Location Agent::Move(Orientation agentOrientation,Location location){
    if(agentOrientation == RIGHT){
        location.X +=1; }
    else if(agentOrientation == UP){
        location.Y +=1;}
    else if(agentOrientation == LEFT){
        location.X -=1;}
    else if(agentOrientation == DOWN){
        location.Y -=1;}

    return location;
}

Action Agent::Process (Percept& percept)
{
    cout<< "X:" << currentLocation.X << "Y:" << currentLocation.Y << endl;
	list<Action> actionList2;
    safeLocations.push_back(currentLocation);
    visitedLocations.push_back(currentLocation);
	if (actionList.empty()) {
        if (percept.Glitter){
            cout<< "1:1" << endl;
            actionList.push_back(GRAB);
            goldLocation = currentLocation;
            agentHasGold = true;
        }
        else if (agentHasGold == true && currentLocation == Location(1,1)){
            cout<< "2:2" << endl;
            actionList.push_back(CLIMB);
        }
        else if(! agentHasGold && !(goldLocation == Location(0,0) )) {
            cout<< "3:3" << endl;
			actionList2 = searchEngine.FindPath(currentLocation, agentOrientation, goldLocation, agentOrientation);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(GRAB);
			agentHasGold = true;
		}
        else if(agentHasGold && !(goldLocation == Location(1,1))) {
            cout<< "4:4" << endl;
			actionList2 = searchEngine.FindPath(currentLocation, agentOrientation, Location(1,1),agentOrientation );
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(CLIMB);
		}
        else if(percept.Bump){
            cout<< "5:5" << endl;
            int r = rand()%2;
            if(r==0){
                actionList.push_back(TURNLEFT);
            }
            else if(r==1)
            {
                actionList.push_back(TURNRIGHT);
            }
            Change_face_to(actionList.back(),agentOrientation);
        }
        else{
            cout<< "6:6" << endl;
            int r = rand()%10;
            if(r==0){
                actionList.push_back(TURNLEFT);
            }
            else if(r==1){
                actionList.push_back(TURNRIGHT);
            }
            else{
                actionList.push_back(GOFORWARD);
            }
            Change_face_to(actionList.back(),agentOrientation);
        }
	}
    Action action = actionList.front();
    lastAction = action;
    if (action == GOFORWARD){
        Move(agentOrientation,currentLocation);
    }

	actionList.pop_front();
    cout<< "action:" << action << endl;
	return action;
}

void Agent::GameOver (int score)
{
    if (lastAction == GOFORWARD){
        safeLocations.pop_back();
    }
//    for (int i = 0; i < safeLocations.size()<#condition#>; <#increment#>) {
//        <#statements#>
//    }
    cout<<safeLocations.size()<<endl;

}


