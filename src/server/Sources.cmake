set (SOURCES
	Server.cpp

        #request handlers
        requestHandler/Factory.cpp
        requestHandler/registerUser/Handler.cpp
        requestHandler/registerUser/Processor.cpp
        requestHandler/loginUser/Handler.cpp
        requestHandler/loginUser/Processor.cpp
        requestHandler/createProject/Handler.cpp
        requestHandler/createProject/Processor.cpp
        requestHandler/Factory.cpp

        Database.cpp
    )
