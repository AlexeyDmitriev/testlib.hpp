/*#include "testlib.hpp"
#include <string>
#include <set>

using namespace std;
const int MAXN = 100, MAX_LEN_TEAM = 30;
typedef pair<string, string> TMatch;
typedef pair<int, int> TMatchResult;

inline void isParticipant(const string& curTeam, const set<string>& teams){
	verify(teams.find(curTeam) != teams.end(), Verdict::FAIL, "Matches must be only between participants");
}

inline void addMatch(const TMatch& match, const set<string>& teams, 
		set<TMatch>& playedMatches){
	isParticipant(match.first, teams);
	isParticipant(match.second, teams);
	if (playedMatches.find(match) != playedMatches.end())
		FAIL("Any two teams must play exactly one game");
	if (playedMatches.find(make_pair(match.second, match.first)) != playedMatches.end())
		FAIL("Any two teams must play exactly one game");
	playedMatches.insert(match);
}

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
	set<TMatch> playedMatches;
	for (size_t i = 0; i < n * (n - 1) / 2; ++i){
		TMatch match = inf.read<TMatch>(make_default_reader<string>(MAX_LEN_TEAM), ' ');
		addMatch(match, teams, playedMatches);
		inf.readChar(' ');
		inf.read<TMatchResult>(make_default_reader<int>(0, 10), " : ");
		inf.readEoln();
	}
}
*/
#include "testlib.hpp"
#include <string>
#include <set>

using namespace std;
const int MAXN = 100, MAX_LEN_TEAM = 30;
typedef pair<string, string> TMatch;
typedef pair<int, int> TMatchResult;

inline void isParticipant(const string& curTeam, const set<string>& teams){
	verify(teams.find(curTeam) != teams.end(), Verdict::FAIL, "Matches must be only between participants");
}

inline void addMatch(const TMatch& match, const set<string>& teams,
                     set<TMatch>& playedMatches) {
    isParticipant(match.first, teams);
    isParticipant(match.second, teams);
    if (playedMatches.find(match) != playedMatches.end())
        FAIL("Any two teams must play exactly one game");
    if (playedMatches.find(make_pair(match.second, match.first)) != playedMatches.end())
        FAIL("Any two teams must play exactly one game");
    playedMatches.insert(match);
}


typedef pair<int, int> TMatchResult;
TESTLIB_VALIDATE() {
    size_t n = inf.read<size_t>(1, MAXN);
    inf.readEoln();
    set<string> teams;
    for (size_t i = 0; i < n; ++i) {
        string curTeam = inf.read<string>(MAX_LEN_TEAM);
        for (size_t j = 0; j < curTeam.length(); ++j) {
            verify(curTeam[j] <= 'z' && 'a' <= curTeam[j], Verdict::FAIL, "Incorrect team name"); // проверяем, что имя команды состоит из строчных латинских букв
        }
        verify(teams.find(curTeam) == teams.end(), Verdict::FAIL, "No same team names!");
        teams.insert(curTeam);
        inf.readEoln();
    }
    set<TMatch> playedMatches; // храним множество пар команд, которые уже играли друг с другом
    for (size_t i = 0; i < n * (n - 1) / 2; ++i) {
        TMatch match = inf.read<TMatch>(make_default_reader<string>(MAX_LEN_TEAM), ' '); // читаем пару строк через пробел
        addMatch(match, teams, playedMatches);
        inf.readChar(' ');
        inf.read<TMatchResult>(make_default_reader<int>(0, 10), " : "); // читаем пару чисел (каждое из которых от 0 до 10) с разделителем " : "
        inf.readEoln();
    }
    // Валидатор проверит, что больше ничего в тесте нет (даже пробелов и переводов строк!) и вернет ОК.
}