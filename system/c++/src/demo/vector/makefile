# nmake file
#

TARGET=vector.exe

SOURCES= main.cpp vector.cpp

OBJECTS= $(SOURCES:.cpp=.obj)

all: $(TARGET)

.c.obj:
	$(CXX) /C $(CXXFLAGS) $< /Fo$@

$(TARGET): $(OBJECTS)
    $(CXX) $(CXXFLAGS) $** /Fe$@ 

clean:
	del /q /f $(OBJECTS) $(TARGET)
