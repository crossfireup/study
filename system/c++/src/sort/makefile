# nmake file
#

CXX= cl
CXXFLAGS = /EHsc /nologo 

AS = ml
ASFLAGS = /nologo

TARGET=mergesort.exe

SOURCES= main.cpp mergesort.cpp 

ASMS= $(SOURCES:.cpp=.asm)

OBJECTS= $(SOURCES:.cpp=.obj)

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CXX) $(CXXFLAGS) $** /Fe$@ /Zi 

.cpp.obj:
	$(CXX) $(CXXFLAGS) /c $< /Fa /Fo$@ /FAcs

clean:
	del /q /f $(OBJECTS) $(TARGET) $(OBJECTS:.obj=.asm) *.cod *.pdb
