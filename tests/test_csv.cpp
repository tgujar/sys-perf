#include "csvfile.h"

int main()
{
    try
    {
        csvfile out("test_csv.csv");
        out << "X" << "VALUE" << endrow;
        int i = 1;
        out << i++ << "String value" << endrow;
        out << i++ << 123 << endrow;
        out << i++ << 1.f << endrow;
        out << i++ << 1.2 << endrow;
        out << i++ << "One more string" << endrow;
        out << i++ << "\"Escaped\"" << endrow;
        out << i++ << "=HYPERLINK(\"https://playkey.net\"; \"Playkey Service\")" << endrow;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }
    return 0;
}