set (SOURCES
	Server.cpp

        #request handlers
        requestHandler/Factory.cpp
        requestHandler/user/register/Handler.cpp
        requestHandler/user/register/Processor.cpp
        requestHandler/user/login/Handler.cpp
        requestHandler/user/login/Processor.cpp

        requestHandler/project/createProject/Handler.cpp
        requestHandler/project/createProject/Processor.cpp

        requestHandler/project/sendData/Handler.cpp
        requestHandler/project/sendData/Processor.cpp

        requestHandler/Factory.cpp

    )
