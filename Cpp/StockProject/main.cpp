#include "skynet.h"
#include "misc.h"

using namespace std;

void save(string filename, skynet &obj);

skynet load(string filename, skynet &def);

int main()
{
   skynet networkMgr;
   cout << "initialising\n";
   if (!networkMgr.intitalise("KO", date_time(2003, 1, 1, 1, 1, 1), date_time(2017, 1, 1, 1, 1, 1), 100, 1, 3, 20))
   {
      cout << "failed to intialise\n";
      return -1;
   }

   cout << "training\n";

   vector<double> rms; //stores the root means squared of each run
   char buffer[255];

   rms = networkMgr.RTC(date_time(2004, 1, 1, 1, 1, 1), date_time(2011, 1, 1, 1, 1, 1), 1, 20 * 60 * 60 * 24, 60 * 60 * 24, 0.05);

   networkMgr.run(date_time(2011, 1, 1, 1, 1, 1), date_time(2015, 1, 1, 1, 1, 1), 1, 20 * 60 * 60 * 24, 60 * 60 * 24, "run.csv");

   //save("testSave.txt", networkMgr);
   skynet s = load("testSave.txt", skynet());
   //save("testSave2.txt", s);


   vector<vector<double>> lRRms; //combines learning rate and rms, needs better name but well whatever

   lRRms.push_back(rms);

   createCSV(lRRms, "linearActivation.csv");

   return 0;
}

void save(string filename, skynet &obj)
{
   ofstream file(filename);
   if (file.is_open())
   {
      file << obj.repr();

      file.close();
   }
}

skynet load(string filename, skynet &def)
{
   ifstream file(filename);
   if (file.is_open())
   {
      string obj;
      getline(file, obj);
      file.close();
      if (def.eval(obj))
         cout << "load successful" << endl;
      else
         cout << "BOOOOM" << endl;
   }

   return def;
}