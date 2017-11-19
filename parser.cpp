#include <list>
#include <iostream>
using namespace std;

struct Runner {
  int n = 0;
  int pos = 0;
  string tmp = "";
  string input = "";
};

struct Token {
  string type = "";
  string value = "";

  Token(string t, string v) {
    this->type = t;
    this->value = v;
  }
};

struct Parsec {
  int brackets = 0;
  list<Token> tokens;
  bool validity = true;
};

bool isNull(char c);
bool isSpace(char c);
bool isNumber(char c);
bool isNumSign(char c);
bool isValid(Parsec p);
bool isOperator(char c);
bool isExponent(char c);
bool isOpenBracket(char c);
bool isCloseBracket(char c);
bool isDecimalPoint(char c);

char head(Runner& r);
void getInput(Runner& r);

void S(Runner& runner, Parsec& parsec);
void A(Runner& runner, Parsec& parsec);
void B(Runner& runner, Parsec& parsec);
void C(Runner& runner, Parsec& parsec);
void D(Runner& runner, Parsec& parsec);
void E(Runner& runner, Parsec& parsec);
void F(Runner& runner, Parsec& parsec);
void G(Runner& runner, Parsec& parsec);
void H(Runner& runner, Parsec& parsec);
void I(Runner& runner, Parsec& parsec);
void J(Runner& runner, Parsec& parsec);
void K(Runner& runner, Parsec& parsec);

int main() {
  do {
    Runner runner;
    getInput(runner);

    if (runner.input == "exit") break;

    Parsec parsec;
    runner.n = runner.input.size();

    S(runner, parsec);

    int i = 1;
    int n = parsec.tokens.size();

    cout << "=> ";

    for (Token t : parsec.tokens)
    {
      cout << t.type;

      if (i < n) cout << " "; i++;
    }

    cout << endl;

  } while (true);

  return 0;
}

bool isNull(char c) {
  if (c != '\0') return false;

  return true;
}

bool isSpace(char c) {
  int x = (int) c;

  if (x != 32) return false;

  return true;
}

bool isNumber(char c) {
  int x = (int) c;

  if (!(47 < x && x < 58)) return false;

  return true;
}

bool isNumSign(char c) {
  int x = (int) c;

  if (x != 43 && x != 45) return false;

  return true;
}

bool isValid(Parsec p) {
  if (p.validity == false || p.brackets < 0) return false;

  return true;
}

bool isOperator(char c) {
  int x = (int) c;

  if (x != 120 && x != 43 && x != 45 && x != 58) return false;

  return true;
}

bool isExponent(char c) {
  int x = (int) c;

  if (x != 69) return false;

  return true;
}

bool isOpenBracket(char c) {
  int x = (int) x;

  if (x != 40) return false;

  return true;
}

bool isCloseBracket(char c) {
  int x = (int) c;

  if (x != 41) return false;

  return true;
}

bool isDecimalPoint(char c) {
  int x = (int) c;

  if (x != 44) return false;

  return true;
}

char head(Runner& r) {
  int n = r.input.size();
  char h = r.n < 1 ? '\0' : r.input[r.pos];

  r.pos++;

  return h;
}

void getInput(Runner& r) {
  printf(">> ");
  getline(cin, r.input);
}

void S(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNull(h))
    {
      if (parsec.brackets > 0)
      {
        parsec.validity = false;

        parsec.tokens.pop_back();

        Token token ("ERROR", "(");
        parsec.tokens.push_back(token);
      }
    }
    else if (isSpace(h))
      A(runner, parsec);
    else if (isNumSign(h))
    {
      runner.tmp += h;

      B(runner, parsec);
    }
    else if (isNumber(h))
    {
      runner.tmp += h;

      C(runner, parsec);
    }
    else if (isOpenBracket(h))
    {
      parsec.brackets++;

      Token token ("KURBUKA", "(");
      parsec.tokens.push_back(token);

      S(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void A(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNull(h));
    else if (isSpace(h))
      A(runner, parsec);
    else if (isNumSign(h))
    {
      runner.tmp += h;

      B(runner, parsec);
    }
    else if (isNumber(h))
    {
      runner.tmp += h;

      C(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void B(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNumber(h))
    {
      runner.tmp += h;

      C(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void C(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNull(h))
    {
      if (runner.tmp.size() > 0)
      {
        Token token ("NUM", runner.tmp);
        parsec.tokens.push_back(token);

        runner.tmp = "";
      }
    }
    else if (isNumber(h))
    {
      runner.tmp += h;

      C(runner, parsec);
    }
    else if (isSpace(h))
    {
      Token token ("NUM", runner.tmp);
      parsec.tokens.push_back(token);

      runner.tmp = "";

      D(runner, parsec);
    }
    else if (isDecimalPoint(h))
    {
      runner.tmp += h;

      G(runner, parsec);
    }
    else if (isExponent(h))
    {
      runner.tmp += h;

      I(runner, parsec);
    }
    else if (isCloseBracket(h))
    {
      Token token ("NUM", runner.tmp);
      parsec.tokens.push_back(token);

      runner.tmp = "";

      parsec.brackets--;

      token.value = ")";
      token.type = parsec.brackets < 0 ? "ERROR" : "KURTUTUP";

      if (parsec.brackets < 0) parsec.validity = false;

      parsec.tokens.push_back(token);

      K(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void D(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isSpace(h))
      D(runner, parsec);
    else if (isOperator(h))
    {
      runner.tmp += h;

      Token token ("OPR", runner.tmp);
      parsec.tokens.push_back(token);

      runner.tmp = "";

      E(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void E(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isSpace(h))
      F(runner, parsec);
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void F(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isSpace(h))
      F(runner, parsec);
    else if (isNumber(h))
    {
      runner.tmp += h;

      C(runner, parsec);
    }
    else if (isOpenBracket(h))
    {
      parsec.brackets++;

      Token token ("KURBUKA", "(");
      parsec.tokens.push_back(token);

      S(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void G(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNumber(h))
    {
      runner.tmp += h;

      H(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void H(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNull(h))
    {
      if (runner.tmp.size() > 0)
      {
        Token token ("NUM", runner.tmp);
        parsec.tokens.push_back(token);

        runner.tmp = "";
      }
    }
    else if (isNumber(h))
    {
      runner.tmp += h;

      H(runner, parsec);
    }
    else if (isSpace(h))
    {
      Token token ("NUM", runner.tmp);
      parsec.tokens.push_back(token);

      runner.tmp = "";

      D(runner, parsec);
    }
    else if (isCloseBracket(h))
    {
      Token token ("NUM", runner.tmp);
      parsec.tokens.push_back(token);

      runner.tmp = "";

      parsec.brackets--;

      token.value = ")";
      token.type = parsec.brackets < 0 ? "ERROR" : "KURTUTUP";

      if (parsec.brackets < 0) parsec.validity = false;

      parsec.tokens.push_back(token);

      K(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void I(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNumber(h))
    {
      runner.tmp += h;

      H(runner, parsec);
    }
    else if (isNumSign(h))
    {
      runner.tmp += h;

      J(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void J(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNumber(h))
    {
      runner.tmp += h;

      H(runner, parsec);
    }
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}

void K(Runner& runner, Parsec& parsec) {
  if (isValid(parsec))
  {
    char h = head(runner);

    if (isNull(h))
    {
      if (parsec.brackets > 0)
      {
        parsec.validity = false;

        parsec.tokens.pop_back();

        Token token ("ERROR", "(");
        parsec.tokens.push_back(token);
      }
    }
    else if (isCloseBracket(h))
    {
      parsec.brackets--;

      Token token ("", ")");

      token.type = parsec.brackets < 0 ? "ERROR" : "KURTUTUP";

      if (parsec.brackets < 0) parsec.validity = false;

      parsec.tokens.push_back(token);

      K(runner, parsec);
    }
    else if (isSpace(h))
      D(runner, parsec);
    else
    {
      Token token ("ERROR", "");
      parsec.tokens.push_back(token);

      parsec.validity = false;
    }
  }
}
