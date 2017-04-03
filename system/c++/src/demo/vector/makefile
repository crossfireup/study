# nmake file
#

CXX= cl
CXXFLAGS = /EHsc /nologo 

AS = ml
ASFLAGS = /nologo

TARGET=vector.exe

SOURCES= main.cpp vector.cpp list_container.cpp

ASMS= $(SOURCES:.cpp=.asm)

OBJECTS= $(SOURCES:.cpp=.obj)

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CXX) $(CXXFLAGS) $** /Fe$@

.cpp.obj:
	$(CXX) $(CXXFLAGS) /c $< /Fa /Fo$@

clean:
	del /q /f $(OBJECTS) $(TARGET) $(OBJECTS:.obj=.asm)
