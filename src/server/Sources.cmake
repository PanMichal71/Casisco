set (SOURCES
	Server.cpp

        #request handlers
        requestHandler/Factory.cpp
        requestHandler/user/register/Handler.cpp
        requestHandler/user/register/Processor.cpp
        requestHandler/user/login/Handler.cpp
        requestHandler/user/login/Processor.cpp
        requestHandler/user/Database.cpp

        requestHandler/project/createProject/Handler.cpp
        requestHandler/project/createProject/Processor.cpp

        requestHandler/Factory.cpp

    )
