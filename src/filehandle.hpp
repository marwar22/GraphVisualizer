#ifndef FILEHANDLE_HPP
#define FILEHANDLE_HPP

void WriteBool( bool b, std::ofstream* ff );
bool ReadBool(std::ifstream* ff);
void WriteChar(char c, std::ofstream* ff);
char ReadChar(std::ifstream* ff);
void WriteInt(int n, std::ofstream* ff);
int ReadInt(std::ifstream* ff);
void ReadFile( const char * name, Graph * G );
void WriteFile(const char* name, Graph* G);

#endif