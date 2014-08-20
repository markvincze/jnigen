namespace FTL
{
    class GameEngine
    {
    public:
        int IntVar;

        int IntVar2;

        double DoubleVar;

        std::string StringVar;
    }

    class Player
    {
        std::string Name;

        int Health;
    }

    namespace inner {
        class Parser {
            int MaxFileSize;
        }
    }
}

namespace utils
{
    class GameTool
    {
        std::string RootPath;
    }
}
