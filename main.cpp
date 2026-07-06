#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <unordered_map>

/* void groupedUnary(std::vector<std::string>){
   /* stringParser(std::string); */

bool rightAssociativity(std::string input)
{

  return input == "^";
}

/* bool UnaryMinus(std::vector<std::string> Output, std::stack<std::string> Operator)
{
  if (Output.size() <= Operator.size())
  {
    return true;
  }
  return false;
} */

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

float eval(std::vector<std::string> Output)
{
  std::vector<float> ans;
  int prev = -2;

  for (int i = 0; i < Output.size(); i++)
  {
    if (Output[i] == " ")
      continue;

    if (Output[i] != "/" && Output[i] != "*" && Output[i] != "+" && Output[i] != "-" && Output[i] != "^")
    {
      try
      { // this is a classic incorrect arguement data
        std::cout << Output[i] << std::endl;
        ans.push_back(std::stof(Output[i]));
        prev++;
        /* std::logic_error("foo"); */
      }
      catch (const std::invalid_argument &e)
      {
        std::cout << "hello" << std::endl;
        std::cerr << "Invalid character used" << std::endl;
      }
    }

    else
    {

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
        item = 0.0;
      }

      if (Output[i] == "^")
      {
        item = pow(ans[prev], ans.back());
        ans.pop_back();
        ans.pop_back();
        ans.push_back(item);
        prev--;
        item = 0;
      }
    }
  }

  /*   std::cout << "answer is" << std::endl;
    std::cout << ans[0] << std::endl; */
  return ans.back();
}

std::vector<std::string> stringParser(std::string Input)

{
  std::unordered_map<int, int> GroupedUnaryValidity;
  std::string digits = "";
  std::string symbols = "";
  int characterCount = 0;
  std::string errStatus = "";
  int UnaryGFlag = 0;
  int UnaryFlag = 0;
  int UnaryBegin;
  int UnaryEnd;
  float ans;
  std::vector<std::string> Unary;

  std::vector<std::string> Output;
  std::stack<std::string> Operator;

  for (int i = 0; i < Input.size(); i++)
  {
    if (UnaryGFlag && Input[i] == '(')
    {
      digits = "";
      UnaryBegin = Input.find('(', 0);
      UnaryEnd = Input.find(')', Input.size()-1);
      Unary = stringParser(Input.substr(UnaryBegin, UnaryEnd));
      Unary.push_back("/");
      return Unary;
    }

    /* if (UnaryGFlag && Input[i] == '(')
    {
      UnaryBegin = Input.find('(', 0);
      UnaryEnd = Input.find(')', 0);

      if (UnaryEnd - 1 > UnaryBegin + 2)
      {
        std::cout << "passing to first recursive stringParser" << std::endl;
        Unary = stringParser(Input.substr(UnaryBegin, UnaryEnd));
        std::cout << "returned the parsed input" << std::endl;
        ans = eval(Unary);
        std::cout << "result of the evaluation of the expression without -:" << std::endl;
        std::cout << ans << std::endl;
        std::cout << "passing to the output with - as string" << std::endl;
        std::string correctedAns = std::to_string(ans);
        if (ans <= 0)
        {
          correctedAns.erase(1, 0);
          Output.push_back(correctedAns);
        }
        else
          Output.push_back("-" + std::to_string(ans));
        std::cout << Output[0] << std::endl;
        std::cout << "returning to the Output" << std::endl;
        return Output;
      } */

    if (Input[i] != '+' && Input[i] != '-' && Input[i] != '/' && Input[i] != '*' && Input[i] != '^' && Input[i] != '(' && Input[i] != ')')
    {
  
        if (digits == "-")
        {
          characterCount++;
        }
        digits += Input[i];

        /*  } */
    }
    else
    {

      if (digits != "") // dont push the flushed digit into output.
      {
        {
          Output.push_back(digits);
          characterCount += 1;
        }
        digits = "";
      }

      symbols = Input[i];
      if (symbols == "(")
      {

        /* if(Operator.empty())
        {
          if(Output.back()=="-")
          {
            UnaryFlag=1;
            Output.pop_back();
          }
          if(Output.empty())
          std::cout<<"Hello"<<std::endl;
        } */
        /*  if(Output.back()=="-") */
        if (!Output.empty() && Operator.empty() && !UnaryGFlag)
        {
          std::cout << "err" << std::endl;
          if (errStatus == "")
          {
            std::cout << "invalid sequence of operators" << std::endl;
            errStatus = "-1";
          }
          else
            continue;
        }
        Operator.push(symbols);
        continue;
      }

      if (symbols == ")")
      {
        if (Operator.empty())
        {
          if (errStatus == "") // opening parenthesis deficit
          {
            std::cout << "mismatch of parenthesis (" << std::endl;
            errStatus = "-1";
          }
          else
            continue;
        }

        while (Operator.top() != "(")
        {

          Output.push_back(Operator.top());
          Operator.pop();

          if (Operator.empty())
          {
            if (errStatus == "") // opening parenthesis deficit
            {
              std::cout << "mismatch of parenthesis '('" << std::endl;
              errStatus = "-1";
            }
            else
              continue;
            break;
          }
        }
        if (!Operator.empty())
        {
          Operator.pop();
          continue;
        }
        else
          continue;
      }

      if (symbols == "+" || symbols == "-" || symbols == "/" || symbols == "*" || symbols == "^")
      {
        characterCount -= 1; // handles both parenthesis cases,and non-unary cases

        if (characterCount < 0 && symbols == "-" && i != Input.size() - 2)
        {
          if (i == 0)
          {
            UnaryGFlag = 1;
          }
          UnaryFlag = 1;
          digits += "-";
          continue;
        }

        if (characterCount < 0)
        {
          if (errStatus == "")
          {
            std::cout << "invalid sequence of operators" << std::endl;
            errStatus = "-1";
          }
          else
            continue;
        }

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
  {
    Output.push_back(digits);
    characterCount=+1;
  }


  while (!Operator.empty())
  {
    if (Operator.top() == "(")
    {
      if (errStatus == "") // opening parenthesis deficit
      {
        std::cout << "mismatch of parenthesis ')'" << std::endl;
        errStatus = "-1";
      }
      else
        continue;
    }

    Output.push_back(Operator.top());
    Operator.pop();
  }

  if (characterCount == 0 && UnaryFlag != 1)
  {
    if (errStatus == "")
    {
      std::cout << "wrong sequence of operators" << std::endl;
      errStatus = "-1";
    }
  }

  /* for (std::string &val : Output)
  {
    std::cout << val << std::endl;
  } */
  /*  Output.push_back(errStatus); */

  if (errStatus != "")
  {
    Output.push_back(errStatus);
  }
  /* 3-2*/
  return Output;
}

int main()
{
  std::cout << "Enter your calculations" << std::endl;
  std::cout << "Please end your calculation with =" << std::endl;

  std::vector<std::string> Output;
  std::string Input;
  int groupedUnarySuccess = 0;

  getline(std::cin, Input, '=');

  Output = stringParser(Input);

  std::cout << Output.back() << std::endl;

  if (Output.back() == "/")
  {
    groupedUnarySuccess = 1;
    Output.pop_back();
  }
  std::cout << Output.back() << std::endl;

  if (Output.back() == "-1")
  {
    return -1;
  }

  while (Output.back() == "") // probably nested UNARY operations?
  {
    Output.pop_back();
  }

  float answer = eval(Output);

  if (groupedUnarySuccess == 1 && answer!=0)
  {
    std::cout << -answer << std::endl;
  }
  else
    std::cout << answer << std::endl;

  return 0;
}
