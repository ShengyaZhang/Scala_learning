// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"

#include "Location.h"
#include "Orientation.h"
#include "Search.h"
#include <list>

class MySearchEngine: public SearchEngine {
	virtual int HeuristicFunction (SearchState* state, SearchState* goalState);
};

class Agent
{
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);

	bool agentHasGold;
    bool agentHasArrow;
	list<Action> actionList;
	MySearchEngine searchEngine;

    Orientation agentOrientation;
    Orientation Change_face_to(Action action,Orientation agentOrientation);
    Location Move(Orientation agentOrientation,Location location);
    list<Location> visitedLocations;
    list<Location> safeLocations;
    Location goldLocation;
    Action lastAction;
    Location currentLocation;

};

#endif // AGENT_H
