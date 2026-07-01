#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>


bool rightAssociativity(std::string input){
   
  return input=="^";
}

int Precedence(std::string input)
{
  if (input == "-")
  {
    return 1;
  }

  if (input == "+")
  {
    return 2;
  }

  if (input == "*")
  {
    return 3;
  }

  if (input == "/")
  {
    return 4;
  }

  if (input == "^")
  {
    return 5;
  }
  return -1;
}

std::vector<std::string> stringParser(std::string Input)
{

  std::string digits = "";
  std::string symbols = "";
  std::vector<std::string> Output;
  std::stack<std::string> Operator;

  for (int i = 0; i < Input.size(); i++)
  {
    if (Input[i] != '+' && Input[i] != '-' && Input[i] != '/' && Input[i] != '*' && Input[i] != '^' && Input[i] != '(' && Input[i] != ')')
    {
      digits += Input[i];
    }

    else
    {
      if (digits != "") // dont push the flushed digit into output.
      {
        Output.push_back(digits);
        digits = "";
      }

      symbols = Input[i];
      if (symbols == "(")
      {
        Operator.push(symbols);
        continue;
      }

      if (symbols == ")")
      {
        while (Operator.top() != "(")
        {
          Output.push_back(Operator.top());
          Operator.pop();
        }
        Operator.pop();
        continue;
      }

      if (symbols == "+" || symbols == "-" || symbols == "/" || symbols == "*" || symbols == "^")
      {
        if (Operator.empty() || !Operator.empty() && Precedence(symbols) > Precedence(Operator.top()))

        {
          Operator.push(symbols);
        }

        else
        {
          while (Precedence(symbols) <= Precedence(Operator.top()) && !rightAssociativity(symbols))
          {
            Output.push_back(Operator.top());
            Operator.pop();
            if (Operator.empty()) /*Debugged error,cant apply condition without any stack element*/
              break;
          }
          Operator.push(symbols);
        }
      }
    }
  }

  if (!(digits == ""))
    Output.push_back(digits);

  while (!Operator.empty())
  {
    Output.push_back(Operator.top());
    Operator.pop();
  }

  /* for (std::string &val : Output)
  {
    std::cout << val << std::endl;
  } */

  return Output;
}

int main()
{
  std::cout << "Enter your calculations" << std::endl;
  std::cout << "Please end your calculation with =" << std::endl;
  std::vector<float> ans;
  std::vector<std::string> Output;
  std::string Input;

  getline(std::cin, Input, '=');
  
  Output = stringParser(Input);
  
  int prev = -2;
  for (int i = 0; i < Output.size(); i++)
  {
    if (Output[i] == " ")
      continue;

    if (Output[i] != "/" && Output[i] != "*" && Output[i] != "+" && Output[i] != "-" && Output[i] != "^")
    {
      ans.push_back(std::stoi(Output[i]));
      prev++;
    }

    float item;
    if (Output[i] == "+")
    {
      item = ans[prev] + ans.back();
      ans.pop_back();
      ans.pop_back();
      ans.push_back(item);
      prev--;
      item = 0;
    }

    if (Output[i] == "-")
    {
      item = ans[prev] - ans.back();
      ans.pop_back();
      ans.pop_back();
      ans.push_back(item);
      prev--;
      item = 0;
    }

    if (Output[i] == "*")
    {
      item = ans[prev] * ans.back();
      ans.pop_back();
      ans.pop_back();
      ans.push_back(item);
      prev--;
      item = 0;
    }

    if (Output[i] == "/")
    {
      item = ans[prev] / ans.back();
      ans.pop_back();
      ans.pop_back();
      ans.push_back(item);
      prev--;
      item = 0;
    }


    if (Output[i] == "^")
    {
      item = pow(ans[prev],ans.back());
      ans.pop_back();
      ans.pop_back();
      ans.push_back(item);
      prev--;
      item = 0;
    }
  }
  
  std::cout<<"answer is"<<std::endl;
  std::cout << ans[0] << std::endl;

  return 0;
}
