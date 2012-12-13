#include "testlib.hpp"
#include <string>
#include <set>
#include <map>

using namespace std;
const int MAXN = 100, MAX_LEN_TEAM = 30;

inline void isParticipant(const string& curTeam, const set<string>& teams){
	verify(teams.find(curTeam) != teams.end(), Verdict::FAIL, "Matches must be only between participants");
}

inline void addGame(const string& firstTeam, const string& secondTeam, map<string, set<string>>& played){
	if (played[firstTeam].find(secondTeam) != played[firstTeam].end())
		FAIL("Any two teams must play exactly one game");
	played[firstTeam].insert(secondTeam);
}

typedef pair<int, int> TMatchResult;
TESTLIB_VALIDATE(){
	size_t n = inf.read<size_t>(1, MAXN);
	inf.readEoln();
	set<string> teams;
	for (size_t i = 0; i < n; ++i){
		string curTeam = inf.read<string>(MAX_LEN_TEAM);
		for (size_t j = 0; j < curTeam.length(); ++j){
			verify(curTeam[j] <= 'z' && 'a' <= curTeam[j], Verdict::FAIL, "Incorrect team name");
		}
		verify(teams.find(curTeam) == teams.end(), Verdict::FAIL, "No same team names!");			
		teams.insert(curTeam);
		inf.readEoln();
	}
	map<string, set<string> > played;
	for (size_t i = 0; i < n * (n - 1) / 2; ++i){
		string firstTeam = inf.read<string>(MAX_LEN_TEAM);
		isParticipant(firstTeam, teams);
		inf.readChar(' ');
		string secondTeam = inf.read<string>(MAX_LEN_TEAM);
		isParticipant(secondTeam, teams);
		addGame(firstTeam, secondTeam, played);
		addGame(secondTeam, firstTeam, played);
		inf.readChar(' ');
		inf.read<TMatchResult>(make_default_reader<int>(0, 10), " : ");
		inf.readEoln();
	}
	inf.readEoln();
	for (auto& iter: teams){
		verify(played[iter].size() == n - 1, Verdict::FAIL, "" << iter << "has incorrect number of games");
	}
}
