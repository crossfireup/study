# nmake file
#

CXX= cl
CXXFLAGS = /EHsc /nologo /Zi

AS = ml
ASFLAGS = /nologo

TARGET=mergesort.exe

SOURCES= main.cpp 

ASMS= $(SOURCES:.cpp=.asm)

OBJECTS= $(SOURCES:.cpp=.obj)

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CXX) $(CXXFLAGS) $** /Fe$@ 

.cpp.obj:
	$(CXX) $(CXXFLAGS) /c $< /Fa /Fo$@ /FAcs 

clean:
	del /q /f $(OBJECTS) $(TARGET) $(OBJECTS:.obj=.asm) *.cod *.pdb *.ilk
