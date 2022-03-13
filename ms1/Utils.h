#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds {
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   class Utils {
      bool m_testMode = false;
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);

      // Safely allocates memory in destination and copies the source into it
      void alocpy(char*& destination, const char* source);

      // Continue to prompt the user to enter an integer until a valid one is read
      // Returns the read integer
      int getint(const char* prompt = nullptr);

      // Continue to prompt the user to enter an integer until a valid one within the given range is read
      // Returns the read integer
      int getint(int min, int max, const char* prompt=nullptr, const char* errMes = nullptr);
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
