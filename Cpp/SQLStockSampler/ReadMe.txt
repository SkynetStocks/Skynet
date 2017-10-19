Install mysql at the location C:\Program Files\
While installing define the root user password

Also install boost you can find it at
http://www.boost.org/

install at location
C:\Program Files\boost\

You will need to create a database called skynetserver, you can do this via the command line
This is the tutorial I used to learn how to create a database https://www.youtube.com/watch?v=FAXhXI2Gxdc&t=181s

Now import the tables into skynetserver using mysql workbench
This is a program that should have been installed when you initially installed mysql
Once you open up the mysql workbench program click on database then go down to "connect to database" click that
Then you should see on the left handside of the screen there should be a choice saying "data import/restore"
Import the tables 


Now you should have set up mysql


go to your c++ IDE you need to setup the links and directories
First change the configuration to "Release"
and the Platform to "x64" these are found in the properties menu at the top of window
Second add the directories to boost and the mysqlc++connector
If your using microsoft visual studio's you should be adding something like this
C:\Program Files\boost\boost_1_64_0;C:\Program Files\MySQL\Connector.C++ 1.1\include;
Now setup the linker, no need to link to boost just sql
C:\Program Files\MySQL\Connector.C++ 1.1\lib\opt\mysqlcppconn.lib;
You will also need to add mysqlcppconn.dll to the x64\Release file where the .exe for your program is