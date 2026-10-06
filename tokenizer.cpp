#include "tokenizer.h"
#include<cctype>
using namespace std;

bool Tokenizer::isOperator(char ch)
{ return (ch=='+' ||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^');
}
bool Tokenizer::isParenthesis(  char ch)
{ return (ch=='('|| ch==')');
}

bool Tokenizer::isWhitespace(char ch)
{ return (isspace(static_cast<unsigned char>(ch)));
}

void Tokenizer::tokenize(const string& expression, string tokens[], int& tokenCount)
{
  tokenCount=0;
  int n= expression.length();
  int i=0;
  while(i<n)
  { char current=expression[i];
    if(isWhitespace(current))
     { i++;
       continue;
     }
    if (isdigit(static_cast<unsigned char>(current))|| current=='.')
    { string number;
      bool decimalFound=false;
      while(i<n)
      { char ch= expression[i];
        if(isdigit(static_cast<unsigned char>(ch)))
            { number +=ch;
              i++;
            } 
        else if( ch=='.')
           { if(!decimalFound)
             decimalFound=true;
        number +=ch;
        i++;
            }
        else { break;}
     }
    tokens[tokenCount++]=number;
    continue;
   }

  if(isOperator(current))
  { tokens[tokenCount++]= string(1,current);
    i++;
    continue;
  }
  if(isParenthesis(current))
  { tokens[tokenCount++]=string(1,current);
    i++;
    continue;
  }

tokens[tokenCount++]=string(1,current);
i++;
 }
}
