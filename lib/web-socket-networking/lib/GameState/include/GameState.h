#include <map>
#include <vector>
#include <variant>
#include <string>


using GameValue = std::variant<int, float, std::string, std::vector<std::string>>;
class GameState {
    public:


    private:
        std::map<std::string, GameValue> constants;
        std::map<std::string, GameValue> variables;
};