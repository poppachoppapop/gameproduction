#include "StateManager.h"

void StateManager::Update()
{
	if (!s_states.empty())
		s_states.back()->Update(); // s_states.back() represents the current state running.
}


void StateManager::Render()
{
	if (!s_states.empty())
		s_states.back()->Render();
}

void StateManager::PushState(State* pState)
{
	s_states.push_back(pState); // pState now becomes current state.
	s_states.back()->Enter();
}

void StateManager::PopState() // Used when there are 2 states in vector, i.e., Game and Pause.
{
	if (s_states.size() <= 1) return;
	if (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; //Wrangles state.
		s_states.pop_back(); // Removes nullptr to deallocated current state.
	}
	s_states.back()->Resume();
}

void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}// same function as if statement above in PopState.

	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates() { return s_states; }

std::vector<State*> StateManager::s_states; // Vector is now allocated memory. 'exists' in program.
