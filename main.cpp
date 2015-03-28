#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

#include "util.h"
#include "expreval.h"
#include "context.h"
#include "expression.h"

Context<double> doubleContext;
Context<string> stringContext;
ExprEval eval(doubleContext, stringContext);

string cast(string param){
    cout << "casting - " << param << endl;
    return "";
}

string getLeftVarName(string left){
     string varName = left.substr(left.find(" "), left.length());
     varName = Util::trim(varName);
     return varName;
}

void interpretLeftRight(string left, string right){
     cout << left << ", " << right << endl;
     if(left.substr(0, 3) == "int"){
         string varName = getLeftVarName(left);
         doubleContext.createVar(varName);
         
         if(!right.empty()){
             cout << " - int z przypisaniem";
             doubleContext.assignVar(varName, eval.evalDouble(right));
         }
         else cout << " - int bez przypisania";
     }
     else if(left.substr(0, 6) == "string"){
         if(!right.empty()){
             cout << " - string z przypisaniem";
         }
         else cout << " - string bez przypisania";
     }
     //funkcja
     //zmienna
     
     cout << endl;
}

void parseLine(string line)
{
     string left, right;
     for(int i=0; i<line.length(); i++)
     {
         if(line[i] == '='){
             left = line.substr(0, i); 
             left = Util::trim(left);
             right = line.substr(i + 1, line.length());
             right = Util::trim(right);
             break;
         }else
         {
              left = line;
              left = Util::trim(left);
              right = "";
         }      
     }
     
     interpretLeftRight(left, right);
}

int main(int argc, char* argv[]) 
{
   /* if (argc < 2) {
            std::cerr << "parser.exe plik.txt" << std::endl;
            return 1;
    }*/
    
    ifstream parsedFile("plik.txt"/*argv[1]*/);
    string line;
    
    if(parsedFile.is_open())
    {
    	try
    	{         
            while ( getline (parsedFile, line) )
            {
                if(line.length() < 2)continue;                
                parseLine(line);                                
            }
                           	
               
            
            //stringContext.createFunc("cast", cast);
            //cout << stringContext.callFunc(string("cast"), string("param1, param2")) << endl;
                 
            string strexpr("1+4*num;");
            //cout << strexpr << endl;
    
    	    
            eval.evalDouble(strexpr);             
            
            //eval.evalString("\"milgo \"+napis + cast(string, s) + \"hello\";");
            
    	}	
    	catch(string e)
    	{
    		cout << "Exception: " << e << endl;
    	}
    	
    	parsedFile.close();
    }
    system("PAUSE");
}
